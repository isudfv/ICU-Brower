//
// Created by liang on 22-4-20.
//

#ifndef QBROWSERCLIENT__QBROWSERWINDOW_H_
#define QBROWSERCLIENT__QBROWSERWINDOW_H_

#include <QQuickWindow>
#include "cef_browser.h"

class QBrowserWindow : public QWindow {
 Q_OBJECT

 public:
  QBrowserWindow() = default;
  virtual ~QBrowserWindow() override = default;

  explicit QBrowserWindow(const CefString &url);

  // callback method
  void setBrowserId(int browser_id);

  void setBrowserUrl(const QString &url);

  void setLoadingState(bool isLoading, bool canGoBack, bool canGoForward);

  void setClosingState(bool isClosing);

  // user method
  void setAdBlockFlag(bool flag);

  void doLoadUrl(const QString &url);

  void doReload();

  void doStopLoad();

  void doGoBack();

  void doGoForward();

  // Qt event
  void resizeEvent(QResizeEvent *ev) override;

  void closeEvent(QCloseEvent *) override;

  void moveEvent(QMoveEvent *) override;

 private:
  int browser_id_;
  QString browser_url_;
  bool is_closing_ = false;
  bool is_loading_ = false;
  bool can_go_back_ = false;
  bool can_go_forward_ = false;
};

#endif //QBROWSERCLIENT__QBROWSERWINDOW_H_
