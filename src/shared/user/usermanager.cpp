#include "usermanager.h"
#include "browserprofile.h"
#include <iostream>


int getNumber(Database &database)
{
    Collection   coll   = database["counter"];
    auto         result = coll.find_one_and_update(DocumentStreamBuilder{} << "_id"
                                                                           << "uid" << bsoncxx::builder::stream::finalize,
                                                   DocumentStreamBuilder{} << "$inc" << bsoncxx::builder::stream::open_document
                                                                           << "sequence_number" << 1
                                                                           << bsoncxx::builder::stream::close_document
                                                                           << bsoncxx::builder::stream::finalize);
    DocumentView view   = result->view();
    return view["sequence_number"].get_value().get_int32() + 1;
}

Q_INVOKABLE void UserManager::doLogin(const QString &username, const QString &password, QJSValue callback)
{
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;
    using bsoncxx::document::element;
    using bsoncxx::document::value;

    QJSValueList list;
    int          uid;

    //    qDebug() << "here1";

    //创建数据库实例
    //Instance inst = {};
    //    Uri      uri("mongodb://175.178.155.66:27017");
    //    qDebug() << "here2";

    //连接数据库实例
    Database                       db   = client["browser"];
    Collection                     coll = db["user"];
    element                        ele;
    bsoncxx::stdx::optional<value> find_one;

    //先查找用户名是否存在
    find_one = coll.find_one(document{} << "username" << username.toStdString() << finalize);
    //用户不存在
    //    qDebug() << "here3";
    if (!find_one) {
        list = {UserNotExist};
        goto CALLBACK;
    }

    ele = find_one->view()["password"];
    //用户存在，则判断密码是否正
    if (ele.get_utf8().value.to_string() != password.toStdString()) {
        list = {PasswordError};
        goto CALLBACK;
    }

    ele  = find_one->view()["_id"];
    uid  = ele.get_int32().value;
    list = {LoginSuccess, uid};
//调用回调函数，返回给view层用户的uid
CALLBACK:
    callback.call(list);
    //    qDebug() << "called";
}
Q_INVOKABLE void UserManager::doRegister(const QString &username, const QString &password, QJSValue callback)
{
    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;
    using bsoncxx::document::element;
    using bsoncxx::document::value;

    QJSValueList list;
    auto         pwdLen  = password.length();
    auto         nameLen = username.length();

    //创建数据库实例
    //    Instance inst = {};
    //    Uri      uri("mongodb://175.178.155.66:27017");
    //    Client   client(uri);

    //连接数据库实例
    Database                                              db   = client["browser"];
    Collection                                            coll = db["user"];
    element                                               ele;
    bsoncxx::stdx::optional<value>                        find_one;
    bsoncxx::stdx::optional<mongocxx::result::insert_one> result_insert_one;

    //先判断名字是否合法
    if (nameLen < 6 || nameLen > 16) {
        //        qDebug() << username << nameLen;
        list = {UserNameLengthViolation};
        goto CALLBACK;
    }

    //判断密码长度是否合法
    if (pwdLen < 8 || pwdLen > 16) {
        list = {PwdLengthViolation};
        goto CALLBACK;
    }

    //在表中查找过滤
    find_one = coll.find_one(document{} << "username" << username.toStdString() << finalize);
    //如果找到了重复的,则报错
    if (find_one) {
        list = {UserAlreadyExist};
        goto CALLBACK;
    }

    //向表中插入
    result_insert_one = coll.insert_one(document{} << "username" << username.toStdString()
                                                   << "password" << password.toStdString()
                                                   << "_id" << getNumber(db)
                                                   << finalize);
    if (result_insert_one) {
        list = {RegisterSuccess};
        goto CALLBACK;
    }
    // 插入失败
    list = {DBInsertFailure};

//调用回调函数，给view层显示状态
CALLBACK:
    callback.call(list);
}

Q_INVOKABLE void UserManager::doLogout(QJSValue callback)
{
    //设置uid为0，调用回调函数进行view层更新显示
    QJSValue     _id(0);
    QJSValueList list;
    list.append(_id);
    callback.call(list);
}

DocumentValue toBson(QJsonObject& obj)
{
    /*
    将json转换成string，再将string转换成bson
    */
    if(obj.empty())
        return DocumentValue({});
    QJsonDocument doc(obj);
    QByteArray array=doc.toJson(QJsonDocument::Indented);
    std::string json=array.data();
    DocumentValue value=bsoncxx::from_json(json);
    return value;
}
QJsonObject toJson(DocumentValue& value)
{
    //为了保证写回本地之后，仍然是intented的格式，有必要转换成string之后，再转换成document，再写回文件；
    //而不是直接将string写回file
    if(value.view().empty())
        return QJsonObject();
    std::string json=bsoncxx::to_json(value);

//    qDebug()<<QString::fromStdString(json);
    QByteArray array=json.data();
    QJsonDocument doc=QJsonDocument::fromJson(array);
    QJsonObject obj=doc.object();
    return obj;
}
void UserManager::syncHistoryFromLocal(int uid)
{
    //打开用户的历史记录文件
    QString file_path=QString("./history/%1.json").arg(uid);
    QFile file(file_path);
    file.open(QIODevice::ReadWrite);

    //获取到用户的历史记录
    QJsonParseError error;
    QJsonDocument doc=QJsonDocument::fromJson(file.readAll(),&error);
    QJsonObject obj=doc.object();

    //将json格式的记录，转换为bson格式
    DocumentValue value=toBson(obj);

    file.close();

//    qDebug()<<QString::fromStdString(bsoncxx::to_json(value));

    //和数据库建立连接
//    Instance inst{};
//    Uri uri("mongodb://175.178.155.66:27017");
//    Client client(uri);

    Database db=client["browser"];

    Collection coll=db["history"];



    //判断用户是否存在

    /*
        1.构造过滤器
        2.查询结果
        3.如果不存在该用户，则直接insert
        4.如果存在该用户，则直接修改
    */

    DocumentStreamBuilder doc_builder;
    auto result=coll.find_one(DocumentStreamBuilder{}<<"uid"<<uid<<finalize);

    if(!result)
        coll.insert_one(value.view());
    else
    {
        coll.find_one_and_update(DocumentStreamBuilder{}<<"uid"<<uid<<finalize,value.view());
    }

}
void UserManager::syncHistoryToLocal(int uid)
{
    //建立数据库的连接
//    Instance inst={};
//    Uri uri("mongodb://175.178.155.66:27017");
//    Client client(uri);


    Database db=client["browser"];
    Collection coll=db["history"];
    //获取到指定用户的数据

    auto result=coll.find_one(DocumentStreamBuilder{}<<"_id"<<uid<<finalize);


    if(!result) return;

    DocumentValue value=result.value();

    qDebug()<<QString::fromStdString(bsoncxx::to_json(value));

    //数据转换成json格式
    QJsonObject obj=toJson(value);

    //打开json文件，并写回
    QString file_path=QString("./history/%1.json").arg(uid);
    QFile file(file_path);
    file.open(QIODevice::WriteOnly|QIODevice::Truncate);

    QJsonDocument doc;
    doc.setObject(obj);
    QByteArray data=doc.toJson();
    file.write(data);
    file.close();






}
void UserManager::syncFavouriteFromLocal(int uid)
{
    //打开文件
    QString file_path=QString("./favourite/%1.json").arg(uid);
    QFile file(file_path);
    file.open(QIODevice::ReadWrite);

    //获取json文件对象
    QJsonParseError error;
    QJsonDocument doc=QJsonDocument::fromJson(file.readAll(),&error);
    QJsonObject obj=doc.object();

    DocumentValue value=toBson(obj);

//    qDebug()<<QString::fromStdString(bsoncxx::to_json(value));

    file.close();
    //与数据库建立连接
//    Instance inst{};
//    Uri uri("mongodb://175.178.155.66:27017");
//    Client client(uri);

    Database db=client["browser"];
    Collection coll=db["favourite"];

    //判断用户是否存在
    auto result=coll.find_one(DocumentStreamBuilder{}<<"_id"<<uid<<finalize);
    if(!result)
        coll.insert_one(value.view());
    else
    {
        coll.find_one_and_update(DocumentStreamBuilder{}<<"_id"<<uid<<finalize,value.view());
    }



}
void UserManager::syncFavouriteToLocal(int uid)
{
    //和数据库建立连接
//    Instance inst={};
//    Uri uri("mongodb://175.178.155.66:27017");
//    Client client(uri);

    Database db=client["browser"];
    Collection coll=db["favourite"];

    //判断是否存在该用户
    auto result=coll.find_one(DocumentStreamBuilder{}<<"_id"<<uid<<finalize);

    if(!result)
        return;

    //将bson转换成json格式
    DocumentValue value=result.value();
//    qDebug()<<QString::fromStdString(bsoncxx::to_json(value));

    QJsonObject obj=toJson(value);

    QJsonDocument doc(obj);

    //打开本地文件，并写回
    QString file_path=QString("./favourite/%1.json").arg(uid);
    QFile file(file_path);
    file.open(QIODevice::WriteOnly|QIODevice::Truncate);

    QByteArray data=doc.toJson(QJsonDocument::Indented);

    file.write(data);

    file.close();
}

void UserManager::setUserAgent(QString ua)
{
    BrowserProfile::GetInstance()->SetUserAgent(ua);
}

void UserManager::setAdBlockFlag(bool flag)
{
    BrowserProfile::GetInstance()->SetAdBlockFlag(flag);
}
