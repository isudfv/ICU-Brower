#ifndef CEFWINDOW_H
#define CEFWINDOW_H

#include <QObject>
#include <QWidget>
#include <QWindow>

#include "qbrowserwindow.h"

//namespace Ui {
//    class Form;
//}

class CEFWindow : public QBrowserWindow {
 Q_OBJECT
 public:
  CEFWindow();
  explicit CEFWindow(const CefString &url) : QBrowserWindow(url) {}
 public slots:
  void resizeCEFWindow(int x, int y, int width, int height);
};

#endif// CEFWINDOW_H
