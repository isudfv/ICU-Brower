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
#include <QDateTime>

using Qt::endl;
class HistoryManager: public QObject
{
Q_OBJECT
public:
    static HistoryManager *getInstanse()
    {
        static HistoryManager fm;
        return &fm;
    }

    Q_INVOKABLE void addHistory(QString name, QString url, int uid);
    Q_INVOKABLE void removeHistory(QString name, QString url, QString date, QString time, int uid, QJSValue callback);
    Q_INVOKABLE void clearHistory(int uid, QJSValue callback);
    Q_INVOKABLE void loadHistory(int uid, QJSValue callbacka, QJSValue callbackb);
    Q_INVOKABLE void removeSignalDayHistory(int uid, QString date, QJSValue callback);

signals:
    void addItem(QString name, QString url, QString time, QString date);
};

#endif // HISTORYMANAGER_H
