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
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    qmlRegisterType<CEFWindow>("com.fuck.test", 1, 0, "CEFWindow");
    QQmlApplicationEngine engine("qrc:/main.qml");

    QObject *QmlObj    = engine.rootObjects().first();
    QWindow *QmlWindow = qobject_cast<QWindow *>(QmlObj);

    auto cefWindow = new CEFWindow;
    engine.rootContext()->setContextProperty("cefWindow", cefWindow);

    cefWindow->winId();
    cefWindow->setParent(QmlWindow);
    cefWindow->show();

    cefWindow->setGeometry(0, 111, QmlWindow->width(), QmlWindow->height() - 111);


    //    auto   testWidget = new QWidget;
    //    QTimer timer;
    //    QObject::connect(&timer, &QTimer::timeout, [&cefWindow, root = QmlWindow] {
    //        qDebug() << cefWindow->focusObject();
    //        qDebug() << root->focusObject();
    //    });
    //    timer.start(2000);

    //    testWidget->show();
    //    cefWindow->resize(QmlWindow->width(), QmlWindow->height() - 111);
    //    cefWindow->move(0, 111);
    //    cefWindow->setGeometry(0,111,QmlWindow->width(), QmlWindow->height() - 111);
    //    qDebug() << "widget before" << cefWindow->pos();

    //    mywi.setProperty("_q_embedded_native_parent_handle", QVariant(parent_HWND));


    return app.exec();
}
