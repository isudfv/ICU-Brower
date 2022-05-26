//
// Created by liang on 22-4-20.
//

#include "qbrowserwindow.h"
#include "browserclient.h"
#include "windowmanager.h"

#ifdef __linux__
#include <X11/Xlib.h>
#endif

#ifdef _WINDOWS
#endif

void QBrowserWindow::resizeEvent(QResizeEvent *ev)
{
    qDebug("resizing......");
    if (!initialized || is_closing_) return;
#ifdef __linux__
    ::Display *display = cef_get_xdisplay();
    DCHECK(display);
    ::Window window = BrowserClient::GetInstance()->GetBrowserWindowHandler(browser_id_);
    XResizeWindow(display, window, this->geometry().width() * 1.25, this->geometry().height() * 1.25);
    XFlush(display);
#endif
#ifdef _WINDOWS
    HWND window = BrowserClient::GetInstance()->GetBrowserWindowHandler(browser_id_);

    HDC   hdc   = ::GetDC(NULL);
    int   hdpi  = GetDeviceCaps(hdc, LOGPIXELSX);
    float scale = float(hdpi) / 96;

    ::MoveWindow(window, 0, 0,
                 this->width() * scale, this->height() * scale, true);
#endif
}

void QBrowserWindow::moveEvent(QMoveEvent *event)
{
    if (!initialized || is_closing_) return;
#ifdef _WINDOWS
    HWND window = BrowserClient::GetInstance()->GetBrowserWindowHandler(browser_id_);

    HDC   hdc   = ::GetDC(nullptr);
    int   hdpi  = GetDeviceCaps(hdc, LOGPIXELSX);
    float scale = float(hdpi) / 96;

    ::MoveWindow(window, 0, 0,
                 this->width() * scale, this->height() * scale, true);
#endif
}

void QBrowserWindow::closeEvent(QCloseEvent *ev)
{
    qDebug("closing......");

#ifdef __linux__
    if (!is_closing_) {
        BrowserClient::GetInstance()->TryCloseBrowser(browser_id_);
        ev->ignore();
    } else {
        ev->accept();
    }
#endif

#ifdef Q_OS_WIN
    is_closing_ = true;
#endif
}

void QBrowserWindow::setBrowserId(int browser_id)
{
    this->browser_id_ = browser_id;
}

void QBrowserWindow::setLoadingState(bool isLoading, bool canGoBack, bool canGoForward)
{
    this->is_loading_     = isLoading;
    this->can_go_back_    = canGoBack;
    this->can_go_forward_ = canGoForward;

    emit setLoadState(this->browser_id_, this->can_go_back_, this->can_go_forward_);
}

void QBrowserWindow::setClosingState(bool isClosing)
{
    this->is_closing_ = isClosing;
}

QBrowserWindow::QBrowserWindow(const QString &url)
{
    qDebug() << "PARENT================" << g_parent;
    setParent(g_parent);
    BrowserClient::GetInstance()->CreateBrowser(this, url.toStdString());
    setFramePosition({0, 74});
}

void QBrowserWindow::doLoadUrl(const QString &url)
{
    reset();
    BrowserClient::GetInstance()->DoBrowserLoadUrl(browser_id_, url);
}

void QBrowserWindow::doReload()
{
    if (!is_loading_) BrowserClient::GetInstance()->DoBrowserReload(browser_id_);
}

void QBrowserWindow::doGoBack()
{
    reset();
    if (can_go_back_) BrowserClient::GetInstance()->DoBrowserGoBack(browser_id_);
}

void QBrowserWindow::doGoForward()
{
    reset();
    if (can_go_forward_) BrowserClient::GetInstance()->DoBrowserGoForward(browser_id_);
}

void QBrowserWindow::doStopLoad()
{
    reset();
    if (is_loading_) BrowserClient::GetInstance()->DoBrowserStopLoad(browser_id_);
}

void QBrowserWindow::OnCreateFinish()
{
    initialized = true;
    QObject::connect(this,
                     SIGNAL(windowCreated(QBrowserWindow *)),
                     WindowManager::getInstance(),
                     SLOT(addWindow(QBrowserWindow *)));
    QObject::connect(this,
                     SIGNAL(setLoadState(int, bool, bool)),
                     WindowManager::getInstance(),
                     SLOT(loadStateChanged(int, bool, bool)));
    QObject::connect(this,
                     SIGNAL(setTabState(int, const QString &, const QString &, const QString &, bool)),
                     WindowManager::getInstance(),
                     SLOT(tabStateChanged(int, const QString &, const QString &, const QString &, bool)));
    //    QObject::connect(this, SIGNAL(), WindowManager::getInstance(), SLOT());
    //    QObject::connect(this, SIGNAL(), WindowManager::getInstance(), SLOT());
    emit windowCreated(this);
}

int QBrowserWindow::getBrowserId() const
{
    return browser_id_;
}

void QBrowserWindow::activeWindow()
{
    emit setTabState(this->browser_id_, this->title(), this->browser_url_, this->icon_url_, false);
    emit setLoadState(this->browser_id_, this->can_go_back_, this->can_go_forward_);
}

void QBrowserWindow::setBrowserTitle(const QString &title)
{
    emit setTabState(this->browser_id_, title, this->browser_url_, this->icon_url_, title != this->title());
    this->setTitle(title);
}

void QBrowserWindow::setIconUrls(const QString &icon_url)
{
    emit setTabState(this->browser_id_, this->title(), this->browser_url_, icon_url, icon_url_.isEmpty());
    this->icon_url_ = icon_url;
}

void QBrowserWindow::setBrowserUrl(const QString &url)
{
    emit setTabState(this->browser_id_, this->title(), url, this->icon_url_, false);
    this->browser_url_ = url;
}

void QBrowserWindow::reset()
{
    this->setTitle("");
    browser_url_ = "";
    icon_url_    = "";
    is_closing_  = false;
}
