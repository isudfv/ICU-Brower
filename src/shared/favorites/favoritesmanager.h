#ifndef SURFACESFORBOOKMARKS_H
#define SURFACESFORBOOKMARKS_H

#include <QByteArray>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QJSValue>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
class FavoritesManager : public QObject {
    Q_OBJECT
public:
    Q_INVOKABLE void addFavoriteItem(QString url, QString name, QJSValue callBack, int uid);
    Q_INVOKABLE bool getCanFavorite(int uid, QString url);
    Q_INVOKABLE void removeFavoriteItem(int uid, QString url, QJSValue callBack);
    Q_INVOKABLE void loadFavorite(int uid, QJSValue addFavorite, QJSValue callBack);
};

#endif// SURFACESFORBOOKMARKS_H
