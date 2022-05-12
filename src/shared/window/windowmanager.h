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
    Q_INVOKABLE void toggleTab(int windowId);
    Q_INVOKABLE void doGoBack(int windowId);
    Q_INVOKABLE void doGoForward(int windowId);
    Q_INVOKABLE void doReLoad(int windowId);
    Q_INVOKABLE void doLoadUrl(int windowId,QString url,QJSValue callback);
    Q_INVOKABLE void addWindow(QString url);
    Q_INVOKABLE void addWindowNotInFocus(QString url);
    Q_INVOKABLE void removeWindow(int windowId);
signals:
    void addTab(int newWindowId,QString newWindowTitle,bool toToggle);
    void removeTab(int removeWindowId);
    void setState(bool activeBack,
                  bool activeForward,
                  QString currentUrl,
                  QString currentTitle);
public slots:

private:
    int currentWindowId;
    std::map<int,QWindow*> mp;
};

#endif// WINDOWMANAGER_H
