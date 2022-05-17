//
// Created by liang on 22-5-2.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QDownloadWidget.h" resolved

#include "downloaditem.h"

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

void DownloadItem::InitDownload(CefRefPtr<CefDownloadItem> download_item, const CefString &suggested_name) {
  SetFileName(QString::fromStdString(suggested_name));
  SetFullPath("/home/liang/" + file_name_);
  SetStartTime(QDateTime::fromSecsSinceEpoch(download_item->GetStartTime().GetTimeT()));
  SetPercent(download_item->GetPercentComplete());
  SetCurrSpeed(download_item->GetCurrentSpeed());
  SetUrl(download_item->GetURL().ToString().c_str());
}

const QDateTime &DownloadItem::GetEndTime() const {
  return end_time_;
}

void DownloadItem::SetEndTime(const QDateTime &end_time) {
  end_time_ = end_time;
  qDebug() << start_time_ << end_time_ << curr_speed_ << percent_;
}

const QString &DownloadItem::GetUrl() const {
  return url_;
}

void DownloadItem::SetUrl(const QString &url) {
  url_ = url;
}

int64 DownloadItem::GetCurrSpeed() const {
  return curr_speed_;
}

void DownloadItem::SetCurrSpeed(int64 curr_speed) {
  curr_speed_ = curr_speed;
}
