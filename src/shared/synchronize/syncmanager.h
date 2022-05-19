#ifndef SYNCMANAGER_H
#define SYNCMANAGER_H

#include <QCoreApplication>
#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>


typedef bsoncxx::document::value DocumentValue;
typedef bsoncxx::document::view DocumentView;
typedef bsoncxx::builder::stream::document DocumentStreamBuilder;
typedef mongocxx::instance Instance;
typedef mongocxx::client Client;
typedef mongocxx::uri Uri;
typedef mongocxx::database Database;
typedef mongocxx::collection Collection;

using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;

class syncManager:public QObject{
    Q_OBJECT
public:
    void syncHistoryFromLocal(int uid);
    void syncHistoryToLocal(int uid);
    void syncFavouriteFromLocal(int uid);
    void syncFavouriteToLocal(int uid);
};




#endif // SYNCMANAGER_H
