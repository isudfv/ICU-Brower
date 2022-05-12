#include "historymanager.h"

Q_INVOKABLE void HistoryManager::addHistory(QString name,QString time,QString url,int uid,QJSValue callback)
{
    //创建一个history对象
    QJsonObject history;
    history["name"]=name;
    history["time"]=time;
    history["url"]=url;



    //判断history文件夹是否存在.不存在，则创建。专门用来存储history记录
    QDir*folder =new QDir();
    if(!folder->exists("./history"))
    {
        folder->mkdir("./history");
    }
    //打开文件
    QString file_path=QString("./history/%1.json").arg(uid);
    QFile file(file_path);
    file.open(QIODevice::ReadWrite);


    QJsonArray arr;
    QJsonParseError error;
    QJsonDocument doc=QJsonDocument::fromJson(file.readAll(),&error);
    QJsonObject obj=doc.object();

    file.close();
    //如果源文件中已经有内容，则在原有基础上添加
    if(obj.contains("histories"))
    {
        arr=obj["histories"].toArray();
    }
    arr.append(history);
    obj["histories"]=arr;
    obj["uid"]=uid;

    doc.setObject(obj);

    QByteArray data=doc.toJson(QJsonDocument::Indented);

    //将更新后的json文件写回
    QFile out(file_path);
    out.open(QIODevice::WriteOnly|QIODevice::Truncate);
    out.write(data);
    out.close();

    //调用回调函数，修改view层
    QJSValue _name(name);
    QJSValue _url(url);
    QJSValue _time(time);
    QJSValueList list;
    list.append(_name);
    list.append(_time);
    list.append(_url);
    callback.call(list);

}
Q_INVOKABLE void HistoryManager::removeHistory(QString name,QString time,QString url,int uid,QJSValue callback)
{
    QString file_path=QString("./history/%1.json").arg(uid);
    QFile file(file_path);
    file.open(QIODevice::ReadOnly);

    //打开目标文件
    QJsonParseError error;
    QJsonDocument doc=QJsonDocument::fromJson(file.readAll(),&error);
    QJsonObject obj=doc.object();
    QJsonArray arr=obj["histories"].toArray();

    file.close();
    //遍历histories，如果找到符合条件的，就移除
    for(auto it=arr.begin();it!=arr.end();++it)
    {
         QJsonObject temp=it->toObject();
         if(temp["name"].toString()==name&&temp["time"].toString()==time&&temp["url"].toString()==url)
         {
             arr.erase(it);
             break;
         }
    }
    obj["histories"]=arr;
    doc.setObject(obj);
    //将更新后的json写回源文件
    QByteArray data=doc.toJson(QJsonDocument::Indented);
    QFile out(file_path);
    out.open(QIODevice::WriteOnly|QIODevice::Truncate);
    out.write(data);
    out.close();

    //调用回调函数，更新view层的数据
    QJSValue _name(name);
    QJSValue _url(url);
    QJSValue _time(time);
    QJSValueList list;
    list.append(_name);
    list.append(_time);
    list.append(_url);

    callback.call(list);

}
Q_INVOKABLE void HistoryManager::clearHistory(int uid,QJSValue callback)
{
    //以覆盖写方式打开文件
    QString file_path=QString("./history/%1.json").arg(uid);
    QFile file(file_path);
    file.open(QIODevice::WriteOnly|QIODevice::Truncate);

    QJsonDocument doc;
    QJsonObject obj;
    QJsonArray array;
    obj["uid"]=uid;
    obj["history"]=array;
    doc.setObject(obj);

    //将基础的空json写回源文件
    QByteArray data=doc.toJson(QJsonDocument::Indented);

    file.write(data);
    file.close();

    //调用回调函数，更新view层
    callback.call();
}
Q_INVOKABLE void HistoryManager::loadHistory(int uid,QJSValue callbacka,QJSValue callbackb)
{
    //打开文件
    QString file_path=QString("./history/%1.json").arg(uid);
    QFile file(file_path);
    file.open(QIODevice::ReadOnly);

    //获取指定用户的所有history列表
    QJsonParseError error;
    QJsonDocument doc=QJsonDocument::fromJson(file.readAll(),&error);

    QJsonObject obj=doc.object();
    QJsonArray arr=obj["histories"].toArray();

    //调用回调函数，在view层清空上一个用户的列表，并显示当前用户的历史记录列表
    callbacka.call();

    for(auto it=arr.begin();it!=arr.end();++it)
    {
        QJsonObject temp=it->toObject();
        QJSValue _name(temp["name"].toString());
        QJSValue _url(temp["url"].toString());
        QJSValue _time(temp["time"].toString());
        QJSValueList list;
        list.append(_name);
        list.append(_time);
        list.append(_url);
        callbackb.call(list);
    }
    file.close();
}
