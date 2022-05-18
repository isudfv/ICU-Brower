#include "windowmanager.h"
#include "historymanager.h"

void WindowManager::toggleTab(int windowId)
{
    if (mp.count(currentWindowId)) mp[currentWindowId]->hide();
    currentWindowId = windowId;
    mp[currentWindowId]->activeWindow();
}

void WindowManager::doGoBack(int windowId)
{
    mp[windowId]->doGoBack();
}

void WindowManager::doGoForward(int windowId)
{
    mp[windowId]->doGoForward();
}

void WindowManager::doReLoad(int windowId)
{
    mp[windowId]->doReload();
}

void WindowManager::doLoadUrl(int windowId, QString url, int uid)
{
    mp[windowId]->doLoadUrl(url);
}

void WindowManager::addWindow(QString url)
{
    auto *w = new QBrowserWindow(url);
}

void WindowManager::addWindowNotInFocus(QString url)
{
}

void WindowManager::removeWindow(int windowId)
{
    mp.erase(windowId);
    emit removeTab(windowId);
}

void WindowManager::addWindow(QBrowserWindow *new_window)
{
    int id = new_window->getBrowserId();
    mp.insert({id, new_window});
    emit addTab(id, "Loading...", "Loading...", "", true);

    qDebug() << "Add Windows";
}

void WindowManager::tabStateChanged(int windowId, const QString &title, const QString &url, const QString &icon)
{
    emit setTabState(windowId, title, url, icon);

    if (title != "" && url != "" && icon != "") {
//        HistoryManager::getInstanse()->addHistory();
    }

    qDebug() << windowId << title << url << icon;
}

void WindowManager::loadStateChanged(int windowId, bool activeBack, bool activeForward)
{
    if (currentWindowId == windowId) {
        emit setHeaderState(activeBack, activeForward);
    }

    qDebug() << activeForward << activeBack;
}