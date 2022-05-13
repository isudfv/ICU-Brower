#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QCoreApplication>
#include <QJSValue>
#include<QDebug>
#include <QString>

#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include<bsoncxx/builder/basic/document.hpp>
#include<bsoncxx/builder/basic/impl.hpp>
#include<bsoncxx/string/to_string.hpp>
#include<bsoncxx/stdx/string_view.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/types/bson_value/value.hpp>
using bsoncxx::builder::basic::kvp;
using Qt::endl;
using bsoncxx::to_json;

typedef mongocxx::instance Instance;
typedef mongocxx::client Client;
typedef mongocxx::uri Uri;
typedef mongocxx::database Database;
typedef mongocxx::collection Collection;
typedef bsoncxx::builder::basic::document DocumentBuilder;
typedef bsoncxx::document::value DocumentValue;
typedef bsoncxx::document::view DocumentView;


class UserManager:public QObject{
    Q_OBJECT
public:
    Q_INVOKABLE void doLogin(QString username,QString password,QJSValue callback);
    Q_INVOKABLE void doRegister(QString username,QString password,QJSValue callback);
    Q_INVOKABLE void doLogout(QJSValue callback);
    enum registerstate{
        registerSuccess,
        registerFailure,
        userAlreadyExist,
        userNameLengthViolation,
        pwdLengthViolation
    }rstate;
    enum loginstate{
        loginSuccess,
        userNotExist,
        passwordError
    }lstate;
};

#endif // USERMANAGER_H
