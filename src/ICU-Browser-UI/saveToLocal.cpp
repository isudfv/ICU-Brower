#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QByteArray>>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/document/element.hpp>
#include <QIODeviceBase>


//将json文件转存为bson格式
bsoncxx::document::view toBson(const QJsonObject &obj)
{
    if(obj.isEmpty())
        return ::bsoncxx::document::view();

    QJsonDocument doc(obj);
    std::string json=doc.toJson().data();
    return bsoncxx::from_json(json).view();
}
//将bson格式转换为json格式
QJsonObject toJson(bsoncxx::document::view view)
{
    if(view.empty())
        return QJsonObject();

    std::string json=bsoncxx::to_json(view);
    QJsonDocument doc=QJsonDocument::fromJson(QByteArray::fromStdString(json));
    if(doc.isObject())
        return doc.object();
    else
        return QJsonObject();
}
//将bson转化为string
QString getString(bsoncxx::document::view view,
                         std::string key)
{
    if(view.empty())
        return QString();

    bsoncxx::document::element element=view[key];
    if(element.type() == bsoncxx::type::k_utf8)
    {
        std::string value=element.get_utf8().value.to_string();
        return QString::fromStdString(value);
    }
    else
        return QString();
}
//将书签存储到本地
void SaveToLocal(QString name,QString url)
{
    QString file_path="../data/bookmark.json";

    //构建一个书签的json对象
    QJsonObject json;
    json.insert("name",name);
    json.insert("url",url);

    //创建QJsonDocument对象并将新的json对象传入
    QJsonDocument jDoc(json);

    //打开存放json串的文件
    QFile file(file_path);
    if(!file.open(QIODevice::Append))
        return;
    QByteArray data(jDoc.toJson());

    file.write(data);
    file.close();





}
