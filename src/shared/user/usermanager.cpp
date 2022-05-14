#include "usermanager.h"

int getNumber(Database& database)
{
    Collection coll = database["counter"];
    auto result = coll.find_one_and_update(DocumentStreamBuilder{} << "_id" << "uid" << bsoncxx::builder::stream::finalize,
        DocumentStreamBuilder{} << "$inc" <<
        bsoncxx::builder::stream::open_document
        << "sequence_number" << 1
        << bsoncxx::builder::stream::close_document
        << bsoncxx::builder::stream::finalize
        );
    DocumentView view = result->view();
    return view["sequence_number"].get_value().get_int32()+1;
}

Q_INVOKABLE void UserManager::doLogin(QString username,QString password,QJSValue callback)
{
    QJSValueList list;

    //创建数据库实例
    Instance inst={};
    Uri uri("mongodb://localhost:27017");
    Client client(uri);

    //连接数据库实例
    Database db=client["browser"];
    Collection coll=db["user"];
    DocumentBasicBuilder doc_builder;
    //构造过滤器
    doc_builder.append(kvp("username",username.toStdString()));

    //先查找用户名是否存在
    auto find_name=coll.find_one(doc_builder.extract().view());

    //用户不存在
    if(!find_name)
        lstate=userNotExist;
    else
    {
        //用户存在，则判断密码是否正确
        doc_builder.append(kvp("username",username.toStdString()));
        doc_builder.append(kvp("password",password.toStdString()));
        DocumentValue value=doc_builder.extract();
        auto find_user=coll.find_one(value.view());
        if(!find_user)
            lstate=passwordError;
        else
        {
            lstate=loginSuccess;
            DocumentView view=find_user->view();
            //登录成功，则获取用户的id
            int uid=view["_id"].get_value().get_int32();
            QJSValue _uid(uid);
            list.append(_uid);
        }
    }

    QJSValue _state(lstate);
    list.append(_state);

    //调用回调函数，返回给view层用户的uid
    callback.call(list);


}
Q_INVOKABLE void UserManager::doRegister(QString username,QString password,QJSValue callback)
{
    QJSValue _state;
    int pwdLen=password.length();
    int nameLen=username.length();
    //先判断名字是否合法
    if(nameLen<8||nameLen>16)
    {
        rstate=userNameLengthViolation;
    }
    else
    {
        //判断密码长度是否合法
        if(pwdLen<8||pwdLen>16)
        {
            rstate=pwdLengthViolation;
        }
        else
        {
            //建立数据库实例
            Instance inst={};
            //标明数据库地址
            Uri uri("mongodb://localhost:27017");
            //建立数据库连接
            Client client(uri);

            //访问相关的表
            Database db=client["browser"];
            Collection coll=db["user"];

            //创建过滤器
            DocumentBasicBuilder doc_builder;
            doc_builder.append(kvp("username",username.toStdString()));
            doc_builder.append(kvp("password",password.toStdString()));
            DocumentValue value=doc_builder.extract();
            DocumentView view=value.view();

            //在表中查找过滤
            auto result=coll.find_one(view);
            //如果找到了重复的,则报错
            if(result)
            {
                rstate=userAlreadyExist;
            }
            else
            {
                //向表中插入

                //获取当前分配的uid，重新构造一个builder
                int num=getNumber(db);
                DocumentBasicBuilder doc_builder_2;
                doc_builder_2.append(kvp("username",username.toStdString()));
                doc_builder_2.append(kvp("password",password.toStdString()));
                doc_builder_2.append(kvp("_id",num));

                auto result2=coll.insert_one(doc_builder_2.extract().view());
                if(result2)
                    rstate=registerSuccess;
                else rstate=registerFailure;
            }
        }
    }
    //调用回调函数，给view层显示状态
    _state=rstate;
    QJSValueList list;
    list.append(_state);
    callback.call(list);

    return ;
}
Q_INVOKABLE void UserManager::doLogout(QJSValue callback)
{
    //设置uid为0，调用回调函数进行view层更新显示
    QJSValue _id(0);
    QJSValueList list;
    list.append(_id);
    callback.call(list);
}
