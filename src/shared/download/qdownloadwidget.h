//
// Created by liang on 22-5-2.
//

#ifndef QBROWSERCLIENT__QDOWNLOADWIDGET_H_
#define QBROWSERCLIENT__QDOWNLOADWIDGET_H_

#include <QWidget>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class QDownloadWidget; }
QT_END_NAMESPACE

class QDownloadWidget : public QWidget {
 Q_OBJECT

 public:
  using Id = unsigned int;

  explicit QDownloadWidget(QWidget *parent = nullptr);
  explicit QDownloadWidget(Id id, QWidget *parent);
  virtual ~QDownloadWidget() override;

  void setFileName(const QString& file_name);

  void setFullPath(const QString& full_path);

//  void setDownloadControlState(QDateTime start_time, int percent);

  void setDownloadStatus(QDateTime start_time, int percent);

 private:
  Ui::QDownloadWidget *ui;

  Id item_id_;
  QString file_name_;
  QString full_path_;
  int control_state_;

  QDateTime start_time_;
  int percent_ = 0;
};

#endif //QBROWSERCLIENT__QDOWNLOADWIDGET_H_
