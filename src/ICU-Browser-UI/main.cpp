//
// Created by isudfv on 2022/04/17.
//
#include <QApplication>
#include <QLabel>
#include "browserwindow.h"

int main(int argc, char **argv) {
    QCoreApplication::setOrganizationName("QtExamples");
    QApplication app(argc, argv);
//    QApplication::setWindowIcon(QIcon(":/assets/images/back.png"));
    BrowserWindow window;
    window.show();
    window.setURL(QUrl("https://bilibili.com"));


//    app.setWindowIcon(QIcon(QStringLiteral(":AppLogoColor.png")));

//    QWebEngineProfile::defaultProfile()->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
//    QWebEngineProfile::defaultProfile()->settings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);

//    QUrl url = commandLineUrlArgument();

//    Browser        browser;
//    BrowserWindow *window = browser.createWindow();
//    window->tabWidget()->setUrl(url);

    return app.exec();
}
