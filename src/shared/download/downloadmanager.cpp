//
// Created by LotusOvO on 2022/5/14.
//

#include "downloadmanager.h"

void DownloadManager::deleteDownloadItem(int id, QString path){
    QFile::remove(path);
    emit removeItem(id);
}

void DownloadManager::removeDownloadItem(int id, QString path){
    emit removeItem(id);
}

void DownloadManager::clearDownloadItem(){
    emit clearItem();
}

void DownloadManager::showDownLoadItemInExplorer(QString path,QJSValue callback){
    //判断文件不存在则调用回调函数
    QDir dir(path);
    if(false == dir.exists()){
        QJSValueList list{QJSValue(false)};
        callback.call(list);
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

void DownloadManager::updateDowmloadItemState(int id,
                                              int precent,
                                              int currentSpeed){
    emit updateItemState(id, precent, currentSpeed);
}
