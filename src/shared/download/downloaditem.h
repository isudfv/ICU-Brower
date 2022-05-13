//
// Created by liang on 22-5-2.
//

#ifndef QBROWSERCLIENT__QDOWNLOADWIDGET_H_
#define QBROWSERCLIENT__QDOWNLOADWIDGET_H_

#include <QDateTime>
#include <QString>
#include "cef_app.h"

class DownloadItem {
 public:
  using Id = unsigned int;

  explicit DownloadItem(Id id);

  virtual ~DownloadItem() = default;

  void InitDownload(CefRefPtr<CefDownloadItem> download_item, const CefString &suggested_name);

 public:
  const QString &GetFileName() const;
  void SetFileName(const QString &file_name);
  const QString &GetFullPath() const;
  void SetFullPath(const QString &full_path);
  const QDateTime &GetStartTime() const;
  void SetStartTime(const QDateTime &start_time);
  int GetPercent() const;
  void SetPercent(int percent);
  const QString &GetUrl() const;
  void SetUrl(const QString &url);
  int64 GetCurrSpeed() const;
  void SetCurrSpeed(int64 curr_speed);
  const QDateTime &GetEndTime() const;
  void SetEndTime(const QDateTime &end_time);

 private:
  Id item_id_;
  QString file_name_;
  QString full_path_;
  QDateTime start_time_;
  QDateTime end_time_;
  int percent_ = 0;
  QString url_;
  int64 curr_speed_;
};

#endif //QBROWSERCLIENT__QDOWNLOADWIDGET_H_
