#include "usermanager.h"
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
