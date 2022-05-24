#include "favoritesmanager.h"
void FavoritesManager::addFavoriteItem(QString url, QString name, int uid = 0){
    //json文件
    QJsonDocument jDoc;
    //存放书签列表
    QJsonArray    arr;

    //构建一个书签的json对象
    QJsonObject member;
    member.insert("name", name);
    member.insert("url", url);


	//判断文件夹是否存在，不存在就创建一个
    QDir* dir=new QDir();
    if(!dir->exists("./favourite")){
        dir->mkdir("./favourite");
	}
    //打开存放json串的文件
    QString file_path = QString("./favourite/%1.json").arg(uid);
    QFile   file(file_path);
    file.open(QIODevice::ReadWrite);

    //读取文件
    QJsonParseError *error = new QJsonParseError;
    QJsonDocument    jdc   = QJsonDocument::fromJson(file.readAll(), error);

    file.close();

    QJsonObject obj = jdc.object();
    //判断是否文件中有bookmarks列表.如果有，则直接添加到列表当中
    if (obj.contains("bookmarks")) {
        arr = obj["bookmarks"].toArray();
    }
    arr.append(member);

    obj["_id"]       = uid;
    obj["bookmarks"] = arr;
    jDoc.setObject(obj);

    //写回源文件
    QFile out(file_path);
    out.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QByteArray data(jDoc.toJson(QJsonDocument::Indented));

    out.write(data);
    out.close();

    //回调函数，操作view
    emit addFavorite(name,url);
}

bool FavoritesManager::getCanFavorite(int uid, QString url){
    //根据uid，确定文件的存取路径
    QString file_path = QString("./favourite/%1.json").arg(uid);
    QFile   file(file_path);
    file.open(QIODevice::ReadOnly);

    QJsonParseError error;
    QJsonDocument   doc = QJsonDocument::fromJson(file.readAll(), &error);
    QJsonObject     obj = doc.object();
    if (obj.empty())
        return true;
    QJsonArray arr = obj["bookmarks"].toArray();
    for (auto subObj : arr) {
        QJsonObject temp = subObj.toObject();

        if (temp["url"].toString() == url)
            return false;
    }

    file.close();
    return true;
}

void FavoritesManager::removeFavoriteItem(int uid, QString url){
    //打开文件，读取书签列表
    QString file_path = QString("./favourite/%1.json").arg(uid);
    QFile   file(file_path);
    file.open(QIODevice::ReadOnly);

    QJsonParseError error;
    QJsonDocument   doc = QJsonDocument::fromJson(file.readAll(), &error);

    QJsonObject obj = doc.object();
    QJsonArray  arr = obj["bookmarks"].toArray();
    file.close();
    //遍历书签列表，如果找到了目标的url，则删除
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        QJsonObject temp = it->toObject();

        if (temp["url"].toString() == url) {
            arr.erase(it);
            break;
        }
    }
    //将新的书签列表写回原文件
    obj["bookmarks"] = arr;
    doc.setObject(obj);

    QByteArray data(doc.toJson(QJsonDocument::Indented));

    QFile out(file_path);
    out.open(QIODevice::WriteOnly | QIODevice::Truncate);
    out.write(data);
    out.close();

    //回调函数操作view
    emit removeFavorite(url);
}

void FavoritesManager::loadFavorite(int uid){
    //回调函数，清空view层的数据
    emit clearFavorite();
	
	
    //打开文件，获取到书签列表
    QString file_path = QString("./favourite/%1.json").arg(uid);
    QFile   file(file_path);
    file.open(QIODevice::ReadOnly);

    QJsonParseError error;
    QJsonDocument   doc = QJsonDocument::fromJson(file.readAll(), &error);

    QJsonObject obj = doc.object();
    QJsonArray  arr = obj["bookmarks"].toArray();


    //如果书签列表为空，则直接返回
    if (arr.size() == 0)
        return;
    for (auto JsValue : arr) {
        QJsonObject temp = JsValue.toObject();
        qDebug() << temp["name"].toString();
        //调用回调函数，给view层添加单个书签的显示
        emit addFavorite(temp["name"].toString(),temp["url"].toString());
    }
    file.close();
}
