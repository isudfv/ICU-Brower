#include "cefwindow.h"
//#include "form.h"
#include <QApplication>
//#include <QDateTime>
//#include <QGuiApplication>
#include <QLabel>
//#include <QLineEdit>
//#include <QPushButton>
#include <QQmlApplicationEngine>
#include <QQmlContext>
//#include <QQuickItem>
#include <QQuickWidget>

#include "favoritesmanager.h"
#include "historymanager.h"
#include "usermanager.h"
#include "windowmanager.h"
#include "downloadmanager.h"

int main(int argc, char *argv[])
{
    QApplication          app(argc, argv);
    QQmlApplicationEngine engine;

    auto cefWindow        = new CEFWindow;

    engine.rootContext()->setContextProperty("cefWindow", cefWindow);
    engine.rootContext()->setContextProperty("favoritesManager", FavoritesManager::getInstanse());
    engine.rootContext()->setContextProperty("windowManager", WindowManager::getInstanse());
    engine.rootContext()->setContextProperty("historyManager", HistoryManager::getInstanse());
    UserManager::declareQML();

    engine.load("qrc:/main.qml");

    QObject *QmlObj    = engine.rootObjects().first();
    QWindow *QmlWindow = qobject_cast<QWindow *>(QmlObj);

    cefWindow->winId();
    cefWindow->setParent(QmlWindow);
    cefWindow->show();

    cefWindow->setGeometry(0, 111, QmlWindow->width(), QmlWindow->height() - 111);

    //    cefWindow->resize(QmlWindow->width(), QmlWindow->height() - 111);
    //    cefWindow->move(0, 111);
    //    cefWindow->setGeometry(0,111,QmlWindow->width(), QmlWindow->height() - 111);
    //    qDebug() << "widget before" << cefWindow->pos();

    //    mywi.setProperty("_q_embedded_native_parent_handle", QVariant(parent_HWND));

    return app.exec();
}
