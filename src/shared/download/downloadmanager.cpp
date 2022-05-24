//
// Created by LotusOvO on 2022/5/14.
//

#include "downloadmanager.h"

void DownloadManager::deleteDownloadItem(int id, QString path)
{
    QFile::remove(path);
    emit setFileState(id, false);
}

void DownloadManager::removeDownloadItem(int id)
{
    emit removeItem(id);
}

void DownloadManager::clearDownloadItem()
{
    emit clearItem();
}

void DownloadManager::showDownLoadItemInExplorer(int id, QString path)
{
    //判断文件不存在则调用回调函数
    qDebug() << id << path;
    if (!QFileInfo(path).isFile()) {
        emit setFileState(id, false);
        return;
    }
    //打开目录并高亮选中文件
    const QString explorer = "explorer";
    QStringList param;
    if (!QFileInfo(path).isDir()) {
        param << QLatin1String("/select,");
    }
    param << QDir::toNativeSeparators(path);
    QProcess::startDetached(explorer, param);
}

void DownloadManager::downloadItemCreated(int id,
                                          const QString &name,
                                          const QString &url,
                                          const QString &path)
{
    qDebug() << id << name << url << path;
    emit addItem(id, name, url, path);
}

void DownloadManager::downloadItemStateUpdated(int id,
                                               int percent,
                                               int currentSpeed)
{
    qDebug() << id << percent << currentSpeed;
    emit updateItemState(id, percent, currentSpeed);
}

void DownloadManager::changeDownloadItemPauseState(int id)
{
    emit toChangeDownloadItemPauseState(id);
    emit changePauseState(id);
}

void DownloadManager::stopDownload(int id){
    //code here
    emit removeItem(id);
}
