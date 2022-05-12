//
// Created by liang on 22-4-20.
//

#include "qbrowserwindow.h"
#include "browserclient.h"
#include <iostream>

#ifdef __linux__
#include <X11/Xlib.h>
#endif

#ifdef _WINDOWS
#endif

void QBrowserWindow::resizeEvent(QResizeEvent *ev) {
#ifdef __linux__
  ::Display *display = cef_get_xdisplay();
  DCHECK(display);
  if (browser_id_ <= 0) return;
  ::Window window = BrowserClient::GetInstance()->GetBrowserWindowHandler(browser_id_);
  XResizeWindow(display, window, this->geometry().width() * 1.25, this->geometry().height() * 1.25);
  XFlush(display);
#endif
#ifdef _WINDOWS
  if (browser_id_ < 0) return;
  HWND window = BrowserClient::GetInstance()->GetBrowserWindowHanlder(browser_id_);

  HDC hdc = ::GetDC(NULL);
  int hdpi = GetDeviceCaps(hdc, LOGPIXELSX);
  float scale = float(hdpi) / 96;

  ::MoveWindow(window, 0, 0,
               this->width() * scale, this->height() * scale, true);
#endif
}

void QBrowserWindow::setBrowserId(int browser_id) {
  this->browser_id_ = browser_id;
}

void QBrowserWindow::closeEvent(QCloseEvent *ev) {
  qDebug("closing");
#ifdef __linux__
  if (!is_closing_) {
      BrowserClient::GetInstance()->TryCloseBrowser(browser_id_);
      ev->ignore();
  } else {
      ev->accept();
  }
#endif
}

void QBrowserWindow::setBrowserUrl(const QString &url) {
  this->browser_url_ = url;
  qDebug() << browser_url_;
}

void QBrowserWindow::setLoadingState(bool isLoading, bool canGoBack, bool canGoForward) {
  this->is_loading_ = isLoading;
  this->can_go_back_ = canGoBack;
  this->can_go_forward_ = canGoForward;
  qDebug() << isLoading << canGoBack << canGoForward;
}

void QBrowserWindow::setClosingState(bool isClosing) {
  this->is_closing_ = isClosing;
}

QBrowserWindow::QBrowserWindow(const CefString &url) {
  BrowserClient::GetInstance()->CreateBrowser(this, url);
}

void QBrowserWindow::doLoadUrl(const QString &url) {
  BrowserClient::GetInstance()->DoBrowserLoadUrl(browser_id_, url);
}

void QBrowserWindow::doReload() {
  if (!is_loading_) BrowserClient::GetInstance()->DoBrowserReload(browser_id_);
}

void QBrowserWindow::doGoBack() {
  if (can_go_back_) BrowserClient::GetInstance()->DoBrowserGoBack(browser_id_);
}

void QBrowserWindow::doGoForward() {
  if (can_go_forward_) BrowserClient::GetInstance()->DoBrowserGoForward(browser_id_);
}

void QBrowserWindow::doStopLoad() {
  if (is_loading_) BrowserClient::GetInstance()->DoBrowserStopLoad(browser_id_);
}
void QBrowserWindow::moveEvent(QMoveEvent *event) {
#ifdef _WINDOWS
  if (browser_id_ < 0) return;
  qDebug() << this->x() << this->y() << this->width() << this->height();

  HWND window = BrowserClient::GetInstance()->GetBrowserWindowHanlder(browser_id_);

  HDC hdc = ::GetDC(NULL);
  int hdpi = GetDeviceCaps(hdc, LOGPIXELSX);
  float scale = float(hdpi) / 96;

  ::MoveWindow(window, 0, 0,
               this->width() * scale, this->height() * scale, true);
#endif
}
