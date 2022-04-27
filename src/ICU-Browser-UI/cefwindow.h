#ifndef CEFWINDOW_H
#define CEFWINDOW_H

#include <QObject>
#include <QWidget>
#include <QWindow>

//namespace Ui {
//    class Form;
//}

class CEFWindow : public QWindow {
    Q_OBJECT
public:
    CEFWindow();
public slots:
    void resizeCEFWindow(int x, int y, int width, int height);
};

#endif// CEFWINDOW_H
