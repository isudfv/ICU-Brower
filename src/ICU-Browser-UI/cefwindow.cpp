#include "cefwindow.h"
#include <QDebug>

CEFWindow::CEFWindow()
{
    //	setStyleSheet("QMainWindow {background: 'yellow';}");
    setFlag(Qt::FramelessWindowHint);
    browser_url_ = "bilibili.com";
}

void CEFWindow::resizeCEFWindow(int x, int y, int width, int height)
{
    setGeometry(x, y, width, height);
    this->resize(width, height);
    qDebug() << this->size();
    qDebug() << this->position();
}

void CEFWindow::doLoadUrl(const QString &url){
    qDebug() << "Load:" << url;
}

void CEFWindow::doReload(){
    qDebug() << "ReLoad";
}

void CEFWindow::doStopLoad(){
    qDebug() << "StopLoad";
}

void CEFWindow::doGoBack(){
    qDebug() << "GoBack";
}

void CEFWindow::doGoForward(){
    qDebug() << "GoForward";
}

bool CEFWindow::getBackState(){
    return can_go_back_;
}

bool CEFWindow::getForwardState(){
    return can_go_forward_;
}

QString CEFWindow::getUrl(){
    return browser_url_;
}


