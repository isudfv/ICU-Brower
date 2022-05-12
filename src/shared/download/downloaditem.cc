//
// Created by liang on 22-5-2.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QDownloadWidget.h" resolved

#include "downloaditem.h"

void DownloadItem::setDownloadStatus(QDateTime start_time, int percent){
  this->start_time_ = start_time;
  this->percent_ = percent;

  qDebug() << start_time << percent;
}

DownloadItem::DownloadItem(DownloadItem::Id id) {
  this->item_id_ = id;
}
const QString &DownloadItem::GetFileName() const {
  return file_name_;
}
void DownloadItem::SetFileName(const QString &file_name) {
  file_name_ = file_name;
}
const QString &DownloadItem::GetFullPath() const {
  return full_path_;
}
void DownloadItem::SetFullPath(const QString &full_path) {
  full_path_ = full_path;
}
const QDateTime &DownloadItem::GetStartTime() const {
  return start_time_;
}
void DownloadItem::SetStartTime(const QDateTime &start_time) {
  start_time_ = start_time;
}
int DownloadItem::GetPercent() const {
  return percent_;
}
void DownloadItem::SetPercent(int percent) {
  percent_ = percent;
}
void DownloadItem::InitDownload(const std::string &suggested_name) {
  SetFileName(QString::fromStdString(suggested_name));
  SetFullPath(QString::fromStdString("/home/liang/" + suggested_name));
}
