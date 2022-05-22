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

#include "browserprofile.h"
#include "downloadmanager.h"
#include "favoritesmanager.h"
#include "historymanager.h"
#include "usermanager.h"
#include "windowmanager.h"

int main(int argc, char *argv[])
{
    BrowserProfile::InitFromCommandLine(argc, argv);
    QApplication          app(argc, argv);
    QQmlApplicationEngine engine;

    DownloadManager::declareQML();
    FavoritesManager::declareQML();
    HistoryManager::declareQML();
    WindowManager::declareQML();
    UserManager::declareQML();


    engine.load("qrc:/main.qml");

    QObject *QmlObj         = engine.rootObjects().first();
    QWindow *QmlWindow      = qobject_cast<QWindow *>(QmlObj);
    WindowManager::g_parent = QmlWindow;
    emit WindowManager::getInstance()->parentWindowSet();

    BrowserProfile::RunBrowser(QmlWindow);

    BrowserProfile::ShutdownBrowser();

    //    return app.exec();
}
