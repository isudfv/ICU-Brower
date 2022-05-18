//
// Created by liang on 22-4-20.
//

#ifndef QBROWSERCLIENT__QBROWSERWINDOW_H_
#define QBROWSERCLIENT__QBROWSERWINDOW_H_

#include <QQuickWindow>

class QBrowserWindow: public QWindow
{
Q_OBJECT

public:
    QBrowserWindow() = default;
    explicit QBrowserWindow(const QString &url);
    virtual ~QBrowserWindow() override = default;

    void OnCreateFinish();

    // cef callback
    void setBrowserId(int browser_id);
    int getBrowserId() const;

    void setBrowserTitle(const QString &title);

    void setBrowserUrl(const QString &url);

    void setIconUrls(const QString &icon_url);

    void setLoadingState(bool isLoading, bool canGoBack, bool canGoForward);

    void setClosingState(bool isClosing);

    // user method
    void doLoadUrl(const QString &url);

    void doReload();

    void doStopLoad();

    void doGoBack();

    void doGoForward();

    void activeWindow();

    // Qt event
    void resizeEvent(QResizeEvent *ev) override;

    void closeEvent(QCloseEvent *) override;

    void moveEvent(QMoveEvent *) override;

signals:
    void onWindowCreated(QBrowserWindow* );
    void setTabState(int windowId,
                         const QString& title,
                         const QString& url,
                         const QString& icon);
    void setLoadState(int windowId, bool activeBack,
                          bool activeForward);


private:
    bool initialized = false;
    int browser_id_ = 0;

    QString browser_url_;
    QString icon_url_;
    bool is_closing_ = false;
    bool is_loading_ = false;
    bool can_go_back_ = false;
    bool can_go_forward_ = false;
};

#endif //QBROWSERCLIENT__QBROWSERWINDOW_H_
