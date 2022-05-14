#ifndef CEFWINDOW_H
#define CEFWINDOW_H

#include <QObject>
#include <QWidget>
#include <QWindow>
#include <QJSValue>
#include <QJSValueList>
#include <QJSEngine>
//#include "../qbrowserclient/qbrowserwindow.h"

//namespace Ui {
//    class Form;
//}

class CEFWindow : public QWindow {
Q_OBJECT
public:
    CEFWindow();
//  explicit CEFWindow(const CefString &url) : QBrowserWindow(url) {}
public:
    Q_INVOKABLE void resizeCEFWindow(int x, int y, int width, int height);

    Q_INVOKABLE void doLoadUrl(const QString &url);

    Q_INVOKABLE void doReload();

    Q_INVOKABLE void doStopLoad();

    Q_INVOKABLE void doGoBack();

    Q_INVOKABLE void doGoForward();

    Q_INVOKABLE bool getBackState();

    Q_INVOKABLE bool getForwardState();

    Q_INVOKABLE void trying(QString a,QString b,QJSValue callback);

    Q_INVOKABLE QString getUrl();
private:
    int browser_id_;
    QString browser_url_;
    bool is_closing_ = false;
    bool is_loading_ = false;
    bool can_go_back_ = true;
    bool can_go_forward_ = true;
};

#endif// CEFWINDOW_H
