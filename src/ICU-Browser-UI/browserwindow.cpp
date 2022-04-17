//
// Created by isudfv on 2022/04/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BrowserWindow.h" resolved

#include "browserwindow.h"
#include "ui_BrowserWindow.h"


BrowserWindow::BrowserWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::BrowserWindow) {
    ui->setupUi(this);
    configToolBar();
}

BrowserWindow::~BrowserWindow() {
    delete ui;
}

void BrowserWindow::configToolBar() {
     URLEdit = new QLineEdit(this);
    auto action  = new QAction(this);
    URLEdit->addAction(action, QLineEdit::LeadingPosition);
    URLEdit->setClearButtonEnabled(false);
    ui->toolBar->addWidget(URLEdit);

    auto downloadsAction = new QAction(this);
    downloadsAction->setIcon(QIcon(":/images/download.png"));
    downloadsAction->setToolTip(tr("Show downloads"));
    ui->toolBar->addAction(downloadsAction);
    connect(downloadsAction, &QAction::triggered, [this]() {
//        m_browser->downloadManagerWidget().show();
    });
}
void BrowserWindow::setURL(const QUrl& url) {
    URLEdit->setText(url.toString());
}
