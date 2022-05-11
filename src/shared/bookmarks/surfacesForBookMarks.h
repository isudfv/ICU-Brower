#ifndef SURFACESFORBOOKMARKS_H
#define SURFACESFORBOOKMARKS_H

#include <QCoreApplication>
#include<QDebug>
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include<QJsonArray>
#include<QJSValue>
class FavouritesManager{
public:
    void addFavouriteItem(QString url,QString name,QJSValue addFavouriteIte,int uid);
    bool getCanFavorite(int uid,QString url);
    void removeFavouriteItem(int uid,QString url,QJSValue removeFavouriteItem);
    void loadFavourite(int uid,QJSValue addFavourite,QJSValue clearFavourite);
};

#endif // SURFACESFORBOOKMARKS_H
