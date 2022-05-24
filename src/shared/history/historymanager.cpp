#include "historymanager.h"

Q_INVOKABLE void HistoryManager::addHistory(QString name, QString url, int uid) {
    QDateTime datetime = QDateTime::currentDateTime();
    QString date = datetime.date().toString("yyyy-MM-dd");
    QString time = datetime.time().toString("hh:mm");

    //创建一个history对象
    QJsonObject history;
    history["name"] = name;
    history["date"] = date;
    history["time"] = time;
    history["url"] = url;

    //判断history文件夹是否存在.不存在，则创建。专门用来存储history记录
    QDir* folder = new QDir();
    if (!folder->exists("./history")) {
        folder->mkdir("./history");
    }
    //打开文件
    QString file_path = QString("./history/%1.json").arg(uid);
    QFile file(file_path);
    file.open(QIODevice::ReadWrite);

    QJsonArray arr;
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
    QJsonObject obj = doc.object();

    file.close();
    //如果源文件中已经有内容，则在原有基础上添加
    if (obj.contains("history")) {
        arr = obj["history"].toArray();
    }
    arr.append(history);
    obj["history"] = arr;
    obj["_id"] = uid;

    doc.setObject(obj);

    QByteArray data = doc.toJson(QJsonDocument::Indented);

    //将更新后的json文件写回
    QFile out(file_path);
    out.open(QIODevice::WriteOnly | QIODevice::Truncate);
    out.write(data);
    out.close();

    //调用回调函数，修改view层
    emit addItem(name, url, time, date);
    //    QJSValueList list={name,url,time,date};

    //    callback.call(list);
}
Q_INVOKABLE void HistoryManager::removeHistory(QString name, QString url, QString date, QString time, int uid) {
    QString file_path = QString("./history/%1.json").arg(uid);
    QFile file(file_path);
    file.open(QIODevice::ReadWrite);

    //打开目标文件
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
    QJsonObject obj = doc.object();
    QJsonArray arr = obj["history"].toArray();

    file.close();
    //遍历history，如果找到符合条件的，就移除
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        QJsonObject temp = it->toObject();
        if (temp["name"].toString() == name && temp["date"].toString() == date && temp["time"].toString() == time && temp["url"].toString() == url) {
            arr.erase(it);
            break;
        }
    }
    obj["history"] = arr;
    doc.setObject(obj);
    //将更新后的json写回源文件
    QByteArray data = doc.toJson(QJsonDocument::Indented);
    QFile out(file_path);
    out.open(QIODevice::WriteOnly | QIODevice::Truncate);
    out.write(data);
    out.close();

    //调用回调函数，更新view层的数据

    emit removeItem(name, url, time, date);
}
Q_INVOKABLE void HistoryManager::clearHistory(int uid) {
    //以覆盖写方式打开文件
    QString file_path = QString("./history/%1.json").arg(uid);
    QFile file(file_path);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);

    QJsonDocument doc;
    QJsonObject obj;
    QJsonArray array;
    obj["_id"] = uid;
    obj["history"] = array;
    doc.setObject(obj);

    //将基础的空json写回源文件
    QByteArray data = doc.toJson(QJsonDocument::Indented);

    file.write(data);
    file.close();

    //调用回调函数，更新view层
    emit clearItem();
}
Q_INVOKABLE void HistoryManager::loadHistory(int uid, QString keyword) {
    //打开文件
    QString file_path = QString("./history/%1.json").arg(uid);
    QFile file(file_path);
    file.open(QIODevice::ReadWrite);

    //获取指定用户的所有history列表
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);

    QJsonObject obj = doc.object();
    QJsonArray arr = obj["history"].toArray();

    //调用回调函数，在view层清空上一个用户的列表，并显示当前用户的历史记录列表
    emit clearItem();

    for (auto it = arr.begin(); it != arr.end(); ++it) {

        QJsonObject temp = it->toObject();

        QString name = temp["name"].toString();
        QString url = temp["url"].toString();
        QString time = temp["time"].toString();
        QString date = temp["date"].toString();

        if (!keyword.isEmpty() && !findSimilar(name, url, time, date, keyword)) {
            continue;
        }

        emit addItem(name,url,time,date);
    }
    file.close();
}
Q_INVOKABLE void HistoryManager::removeSignalDayHistory(int uid, QString date) {
    //打开文件
    QString file_path = QString("./history/%1.json").arg(uid);
    QFile file(file_path);
    file.open(QIODevice::ReadWrite);

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
    QJsonObject obj = doc.object();
    QJsonArray array = obj["history"].toArray();
    file.close();

    //遍历所有历史记录，将指定date的记录都删除
    for (auto it = array.begin(); it != array.end();) {
        QJsonObject temp = it->toObject();

        if (temp["date"].toString() == date) {
            it = array.erase(it);
        } else
            ++it;
    }
    obj["history"] = array;
    doc.setObject(obj);

    //写回json文件
    QFile out(file_path);
    out.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QByteArray data = doc.toJson(QJsonDocument::Indented);
    out.write(data);
    out.close();

    //调用回调函数，修改view层

    emit removeItemByDate(date);
}


bool HistoryManager::findSimilar(QString& name, QString& url, QString& time, QString& date, QString& keyword) {
    // 待改进的查找算法
    if (name.contains(keyword)|| url.contains(keyword) || time.contains(keyword) || date.contains(keyword)) {
        return true;
    }

    return false;
}
