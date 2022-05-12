#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QCoreApplication>
#include<QDebug>
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include<QJsonArray>
#include<QJSValue>
#include <QDir>
using Qt::endl;
class HistoryManager:public QObject{
    Q_OBJECT
public:
    Q_INVOKABLE void addHistory(QString name,QString time,QString url,int uid,QJSValue callback);
    Q_INVOKABLE void removeHistory(QString name,QString time,QString url,int uid,QJSValue callback);
    Q_INVOKABLE void clearHistory(int uid,QJSValue callback);
    Q_INVOKABLE void loadHistory(int uid,QJSValue callbacka,QJSValue callbackb);

};

#endif // HISTORYMANAGER_H
