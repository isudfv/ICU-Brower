//
// Created by LotusOvO on 2022/5/14.
//

#include "downloadmanager.h"

void DownloadManager::deleteDownloadItem(int id, QString path){
    QFile::remove(path);
    emit setFileState(id,false);
}

void DownloadManager::removeDownloadItem(int id){
    emit removeItem(id);
}

void DownloadManager::clearDownloadItem(){
    emit clearItem();
}

void DownloadManager::showDownLoadItemInExplorer(int id, QString path){
    //判断文件不存在则调用回调函数
    qDebug() << id <<path;
    if(!QFileInfo(path).isFile()){
        emit setFileState(id,false);
        return;
    }
    //打开目录并高亮选中文件
    const QString explorer = "explorer";
    QStringList param;
    if(!QFileInfo(path).isDir()){
        param<< QLatin1String("/select,");
    }
    param << QDir::toNativeSeparators(path);
    QProcess::startDetached(explorer,param);
}

void DownloadManager::createDownloadItem(int id,
                                         QString name,
                                         QString url,
                                         QString path){
    emit addItem(id,name,url,path);
}

void DownloadManager::updateDownloadItemState(int id,
                                              int precent,
                                              int currentSpeed){
    emit updateItemState(id, precent, currentSpeed);
}

void DownloadManager::changeDownloadItemPauseState(int id){
    emit toChangeDownloadItemPauseState(id);
    emit changePauseState(id);
}
