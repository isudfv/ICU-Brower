#include "form.h"
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

int main(int argc, char *argv[])
{
    QApplication          app(argc, argv);
    QQmlApplicationEngine engine("qrc:/main.qml");

    QObject *QmlObj    = engine.rootObjects().first();
    QWindow *QmlWindow = qobject_cast<QWindow *>(QmlObj);


    auto cefWindow = new Form;
    engine.rootContext()->setContextProperty("cefWindow", cefWindow);

    cefWindow->winId();
    cefWindow->windowHandle()->setParent(QmlWindow);
    cefWindow->show();

    cefWindow->resize(QmlWindow->width(), QmlWindow->height() - 111);
    cefWindow->move(0, 111);
    qDebug() << "widget before" << cefWindow->pos();

    //    mywi.setProperty("_q_embedded_native_parent_handle", QVariant(parent_HWND));


    return app.exec();
}
