#include "cefwindow.h"

CEFWindow::CEFWindow()
{
    //	setStyleSheet("QMainWindow {background: 'yellow';}");
    setFlag(Qt::FramelessWindowHint);
}

void CEFWindow::resizeCEFWindow(int x, int y, int width, int height)
{
    setGeometry(x, y, width, height);
    this->resize(width, height);
    qDebug() << this->size();
    qDebug() << this->position();
}
