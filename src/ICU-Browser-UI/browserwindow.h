//
// Created by isudfv on 2022/04/17.
//

#ifndef ICU_BROWSER_BROWSERWINDOW_H
#define ICU_BROWSER_BROWSERWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QUrl>


QT_BEGIN_NAMESPACE
namespace Ui {
    class BrowserWindow;
}
QT_END_NAMESPACE

class BrowserWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit BrowserWindow(QWidget *parent = nullptr);
    void configToolBar();
    void setURL(const QUrl& url);
    ~BrowserWindow() override;

private:
    Ui::BrowserWindow *ui;
    QLineEdit *URLEdit;
};


#endif//ICU_BROWSER_BROWSERWINDOW_H
