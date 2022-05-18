//
// Created by liang on 22-5-2.
//

#ifndef QBROWSERCLIENT__QDOWNLOADWIDGET_H_
#define QBROWSERCLIENT__QDOWNLOADWIDGET_H_

#include <QDateTime>
#include <QString>
#include "cef_app.h"

class DownloadItem : public QObject
{
Q_OBJECT
public:
    using Id = unsigned int;

    explicit DownloadItem(DownloadItem::Id id, CefRefPtr<CefDownloadItemCallback> callback);
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

signals:
    void CreateDownloadItem(int id,
                            const QString &name,
                            const QString &url,
                            const QString &path);
    void UpdateDownloadItemState(int id,
                                 int percent,
                                 int currentSpeed);

public slots:
    void DownloadItemPauseStateChanged(int id);


private:
    Id item_id_;
    QString file_name_;
    QString full_path_;
    QDateTime start_time_;
    QDateTime end_time_;
    int percent_ = 0;
    QString url_;
    int64 curr_speed_;

    //    control methods:
    bool paused_ = false;
    CefRefPtr<CefDownloadItemCallback> callback_;
};

#endif //QBROWSERCLIENT__QDOWNLOADWIDGET_H_
