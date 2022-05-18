//
// Created by LotusOvO on 2022/5/14.
//

#ifndef ICU_BROWSER_UI_DOWNLOADMANAGER_H
#define ICU_BROWSER_UI_DOWNLOADMANAGER_H

#include <QCoreApplication>
#include<QDebug>
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include <QJSValue>
#include <QDir>
#include <QProcess>
#include <QDesktopServices>

#include "downloaditem.h"

class DownloadManager: public QObject
{
Q_OBJECT
public:
    static DownloadManager *getInstance()
    {
        static DownloadManager dm;
        return &dm;
    }

    Q_INVOKABLE void deleteDownloadItem(int id, QString path);
    Q_INVOKABLE void removeDownloadItem(int id);
    Q_INVOKABLE void clearDownloadItem();
    Q_INVOKABLE void showDownLoadItemInExplorer(int id, QString path);
    Q_INVOKABLE void changeDownloadItemPauseState(int id);

signals:
//    to view layer
    void addItem(int id,
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

public slots:
    void downloadItemCreated(int id,
                            const QString &name,
                            const QString &url,
                            const QString &path);
    void downloadItemStateUpdated(int id,
                                  int percent,
                                  int currentSpeed);
};

#endif//ICU_BROWSER_UI_DOWNLOADMANAGER_H
