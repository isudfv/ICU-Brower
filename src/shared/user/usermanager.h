#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QCoreApplication>
#include <QDebug>
#include <QJSValue>
#include <QQmlEngine>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/impl.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/string_view.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/types/bson_value/value.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
using bsoncxx::to_json;
using bsoncxx::builder::basic::kvp;
using Qt::endl;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;

typedef mongocxx::instance                 Instance;
typedef mongocxx::client                   Client;
typedef mongocxx::uri                      Uri;
typedef mongocxx::database                 Database;
typedef mongocxx::collection               Collection;
typedef bsoncxx::builder::basic::document  DocumentBasicBuilder;
typedef bsoncxx::builder::stream::document DocumentStreamBuilder;
typedef bsoncxx::document::value           DocumentValue;
typedef bsoncxx::document::view            DocumentView;


class UserManager : public QObject {
    Q_OBJECT
public:
    explicit UserManager(const char *address) : inst(), client(Uri(address))
    {}

    static UserManager *getInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
    {
        static UserManager *um = new UserManager("mongodb://175.178.155.66:27017");
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        return um;
    }

    //登录接口
    Q_INVOKABLE void doLogin(const QString &username, const QString &password, QJSValue callback);
    Q_INVOKABLE void doRegister(const QString &username, const QString &password, QJSValue callback);
    Q_INVOKABLE void doLogout(QJSValue callback);

    //同步接口
    Q_INVOKABLE void syncHistoryFromLocal(int uid);
    Q_INVOKABLE void syncHistoryToLocal(int uid);
    Q_INVOKABLE void syncFavouriteFromLocal(int uid);
    Q_INVOKABLE void syncFavouriteToLocal(int uid);

    //设置接口
    Q_INVOKABLE void setUserAgent(QString ua);
    Q_INVOKABLE void setAdBlockFlag(bool flag);

    static void declareQML()
    {
        qmlRegisterSingletonType<UserManager>("Managers", 1, 0, "UserManager", getInstance);
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

public:
    Instance inst;
    Client   client;
};

#endif// USERMANAGER_H
