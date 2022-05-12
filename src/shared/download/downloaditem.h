//
// Created by liang on 22-5-2.
//

#ifndef QBROWSERCLIENT__QDOWNLOADWIDGET_H_
#define QBROWSERCLIENT__QDOWNLOADWIDGET_H_

#include <QDateTime>
#include <QString>

class DownloadItem{
 public:
  using Id = unsigned int;

  explicit DownloadItem(Id id);

  virtual ~DownloadItem() = default;

//  void setDownloadControlState(QDateTime start_time, int percent);

  void setDownloadStatus(QDateTime start_time, int percent);

  void InitDownload(const std::string &suggested_name);

 public:
  const QString &GetFileName() const;
  void SetFileName(const QString &file_name);
  const QString &GetFullPath() const;
  void SetFullPath(const QString &full_path);
  const QDateTime &GetStartTime() const;
  void SetStartTime(const QDateTime &start_time);
  int GetPercent() const;
  void SetPercent(int percent);

 private:
  Id item_id_;
  QString file_name_;
  QString full_path_;
  int control_state_;

  QDateTime start_time_;
  int percent_ = 0;
};

#endif //QBROWSERCLIENT__QDOWNLOADWIDGET_H_
