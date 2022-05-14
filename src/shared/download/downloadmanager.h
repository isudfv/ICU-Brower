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

class DownloadManager:public QObject{
    Q_OBJECT
public:
    static DownloadManager* getInstanse(){
        static DownloadManager dm;
        return &dm;
    }

    Q_INVOKABLE void deleteDownloadItem( QString path,QJSValue callback);
    Q_INVOKABLE void removeDownloadItem(int id);
    Q_INVOKABLE void clearDownloadItem();
    Q_INVOKABLE void showDownLoadItemInExplorer(QString path,QJSValue callback);

signals:
    void addItem(int id,
                 QString name,
                 QString url,
                 QString path);
    void removeItem(int id);
    void clearItem();
    void updateItemState(int id,
                         int precent,
                         int currentSpeed);

public slots:
    void createDownloadItem(int id,
                            QString name,
                            QString url,
                            QString path);
    void updateDowmloadItemState(int id,
                                 int precent,
                                 int currentSpeed);
};

#endif//ICU_BROWSER_UI_DOWNLOADMANAGER_H
