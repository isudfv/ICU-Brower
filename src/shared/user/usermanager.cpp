#include "usermanager.h"


Q_INVOKABLE void UserManager::doLogin(QString username,QString password,QJSValue callback)
{
    qDebug()<<"123"<<Qt::endl;
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
            DocumentBuilder doc_builder;
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
                auto result2=coll.insert_one(view);
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

    qDebug()<<rstate;
    return ;
}
Q_INVOKABLE void UserManager::doLogout(QJSValue callback)
{

}
