#ifndef CEFWINDOW_H
#define CEFWINDOW_H

#include <QObject>
#include <QWidget>
#include <QWindow>

//#include "../qbrowserclient/qbrowserwindow.h"

//namespace Ui {
//    class Form;
//}

class CEFWindow : public QWindow {
 Q_OBJECT
 public:
  CEFWindow();
//  explicit CEFWindow(const CefString &url) : QBrowserWindow(url) {}
 public slots:
  void resizeCEFWindow(int x, int y, int width, int height);

  void doLoadUrl(const QString &url);

  void doReload();

  void doStopLoad();

  void doGoBack();

  void doGoForward();

  bool getBackState();

  bool getForwardState();

  QString getUrl();
private:
   int browser_id_;
   QString browser_url_;
   bool is_closing_ = false;
   bool is_loading_ = false;
   bool can_go_back_ = true;
   bool can_go_forward_ = true;
};

#endif// CEFWINDOW_H
