//
// Created by LotusOvO on 2022/5/14.
//

#ifndef ICU_BROWSER_UI_DOWNLOADMANAGER_H
#define ICU_BROWSER_UI_DOWNLOADMANAGER_H

#include <QByteArray>
#include <QCoreApplication>
#include <QDebug>
#include <QDesktopServices>
#include <QDir>
#include <QFile>
#include <QJSValue>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QQmlEngine>
#include <QString>

#include "downloaditem.h"

class DownloadManager : public QObject {
    Q_OBJECT
public:
    static DownloadManager *getInstance(QQmlEngine *engine = nullptr, QJSEngine *scriptEngine = nullptr)
    {
        static auto *dm = new DownloadManager;
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        return dm;
    }

    static void declareQML()
    {
        qmlRegisterSingletonType<DownloadManager>("Managers", 1, 0, "DownloadManager", getInstance);
    }

    Q_INVOKABLE void deleteDownloadItem(int id, QString path);
    Q_INVOKABLE void removeDownloadItem(int id);
    Q_INVOKABLE void clearDownloadItem();
    Q_INVOKABLE void showDownLoadItemInExplorer(int id, QString path);
    Q_INVOKABLE void changeDownloadItemPauseState(int id);
    Q_INVOKABLE void stopDownload(int id);

signals:
    //    to view layer
    void addItem(int     id,
                 QString name,
                 QString url,
                 QString path);
    void removeItem(int id);
    void clearItem();
    void updateItemState(int id,
                         int percent,
                         int currentSpeed);
    void setFileState(int id, bool exist);
    void changePauseState(int id);


    //    to model layer
    void toChangeDownloadItemPauseState(int id);
    void toStopDownloadItem(int id);

public slots:
    void downloadItemCreated(int            id,
                             const QString &name,
                             const QString &url,
                             const QString &path);
    void downloadItemStateUpdated(int id,
                                  int percent,
                                  int currentSpeed);
};

#endif//ICU_BROWSER_UI_DOWNLOADMANAGER_H
