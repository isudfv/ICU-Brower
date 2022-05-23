#ifndef SURFACESFORBOOKMARKS_H
#define SURFACESFORBOOKMARKS_H

#include <QByteArray>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJSValue>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQmlEngine>
#include <QString>
using Qt::endl;
class FavoritesManager : public QObject {
    Q_OBJECT
public:

    static FavoritesManager *getInstance(QQmlEngine *engine = nullptr, QJSEngine *scriptEngine = nullptr)
    {
        static auto *fm = new FavoritesManager;
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        return fm;
    }

    static void declareQML()
    {
        qmlRegisterSingletonType<FavoritesManager>("Managers", 1, 0, "FavoritesManager", getInstance);
    }

    Q_INVOKABLE void addFavoriteItem(QString url, QString name, int uid);
    Q_INVOKABLE bool getCanFavorite(int uid, QString url);
    Q_INVOKABLE void removeFavoriteItem(int uid, QString url);
    Q_INVOKABLE void loadFavorite(int uid);

signals:
    void addFavorite(QString name,QString url);
    void clearFavorite();
    void removeFavorite(QString url);
};

#endif// SURFACESFORBOOKMARKS_H
