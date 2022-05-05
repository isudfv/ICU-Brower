//
// Created by liang on 22-5-2.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QDownloadWidget.h" resolved

#include "qdownloadwidget.h"

#include <utility>
#include "ui_qdownloadwidget.h"

QDownloadWidget::QDownloadWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::QDownloadWidget) {
  ui->setupUi(this);
}

QDownloadWidget::~QDownloadWidget() {
  delete ui;
}
QDownloadWidget::QDownloadWidget(Id id, QWidget *parent) :
    item_id_(id), QWidget(parent), ui(new Ui::QDownloadWidget) {
  ui->setupUi(this);
}
void QDownloadWidget::setFileName(const QString& file_name) {
  this->file_name_ = file_name;
}
void QDownloadWidget::setFullPath(const QString& full_path) {
  this->full_path_ = full_path;
}
void QDownloadWidget::setDownloadStatus(QDateTime start_time, int percent){
  this->start_time_ = start_time;
  this->percent_ = percent;

  qDebug() << start_time << percent;
}
