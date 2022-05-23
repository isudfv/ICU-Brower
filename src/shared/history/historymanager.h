#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QByteArray>
#include <QCoreApplication>
#include <QDateTime>
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
class HistoryManager : public QObject {
    Q_OBJECT
public:
    static HistoryManager *getInstance(QQmlEngine *engine = nullptr, QJSEngine *scriptEngine = nullptr)
    {
        static auto *hm = new HistoryManager;
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        return hm;
    }

    static void declareQML()
    {
        qmlRegisterSingletonType<HistoryManager>("Managers", 1, 0, "HistoryManager", getInstance);
    }

    Q_INVOKABLE void addHistory(QString name, QString url, int uid);
    Q_INVOKABLE void removeHistory(QString name, QString url, QString date, QString time, int uid, QJSValue callback);
    Q_INVOKABLE void clearHistory(int uid, QJSValue callback);
    Q_INVOKABLE void loadHistory(int uid, QJSValue callbacka, QJSValue callbackb, QString keyword = "");
    Q_INVOKABLE void removeSignalDayHistory(int uid, QString date, QJSValue callback);
    bool             findSimilar(QString &name, QString &url, QString &time, QString &date, QString &keyword);

signals:
    void addItem(QString name, QString url, QString time, QString date);
};

#endif// HISTORYMANAGER_H
