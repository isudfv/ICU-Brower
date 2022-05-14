﻿#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QCoreApplication>
#include <QDebug>
#include <QJSValue>
#include <QQmlEngine>
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
typedef bsoncxx::builder::basic::document DocumentBasicBuilder;
typedef bsoncxx::builder::stream::document DocumentStreamBuilder;
typedef bsoncxx::document::value DocumentValue;
typedef bsoncxx::document::view DocumentView;


class UserManager : public QObject {
    Q_OBJECT
public:
    static QObject *getInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
    {
        static UserManager um;
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        return &um;
    }

    Q_INVOKABLE static void doLogin(const QString &username, const QString &password, QJSValue callback);
    Q_INVOKABLE static void doRegister(const QString &username, const QString &password, QJSValue callback);
    Q_INVOKABLE static void doLogout(QJSValue callback);

    static void declareQML()
    {
        qmlRegisterSingletonType<UserManager>("UserManager", 1, 0, "UserManager", getInstance);
    }

    enum registerState {
        RegisterSuccess,
        DBInsertFailure,
        UserAlreadyExist,
        UserNameLengthViolation,
        PwdLengthViolation
    };

    enum loginState {
        LoginSuccess,
        UserNotExist,
        PasswordError
    };

    Q_ENUM(registerState)
    Q_ENUM(loginState)
};

#endif // USERMANAGER_H