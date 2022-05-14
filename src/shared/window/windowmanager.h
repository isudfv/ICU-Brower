#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QByteArray>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QJSValue>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QWindow>
#include <map>
class WindowManager : public QObject {
    Q_OBJECT
public:
    static WindowManager* getInstanse(){
        static WindowManager wm;
        return &wm;
    }

    Q_INVOKABLE void toggleTab(int windowId);
    Q_INVOKABLE void doGoBack(int windowId,QJSValue callback);
    Q_INVOKABLE void doGoForward(int windowId,QJSValue callback);
    Q_INVOKABLE void doReLoad(int windowId,QJSValue callback);
    Q_INVOKABLE void doLoadUrl(int windowId,QString url,QJSValue callback);
    Q_INVOKABLE void addWindow(QString url);
    Q_INVOKABLE void addWindowNotInFocus(QString url);
    Q_INVOKABLE void removeWindow(int windowId);
    int getIndex();
signals:
    void addTab(int newWindowId,QString newWindowTitle,QString newWindowUrl,QString icon,bool toToggle);
    void removeTab(int removeWindowId);
    void setHeaderState(bool activeBack,
                  bool activeForward);
    void setTabState(QString title,
                     QString url,
                     QString icon);
public slots:

private:
    int currentWindowId;
    std::map<int,QWindow*> mp;
};

#endif// WINDOWMANAGER_H
