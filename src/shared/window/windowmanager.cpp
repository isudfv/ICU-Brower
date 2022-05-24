#include "windowmanager.h"
#include "historymanager.h"

void WindowManager::toggleTab(int windowId)
{
    if (mp.count(currentWindowId)) mp[currentWindowId]->hide();
    currentWindowId = windowId;
    if (mp.count(currentWindowId)) {
        mp[currentWindowId]->activeWindow();
        mp[currentWindowId]->show();
    }
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
    //    QObject::connect(w, &QBrowserWindow::windowCreated, this, &WindowManager::windowCreated);
    //    QObject::connect(w, &QBrowserWindow::windowCreated, this, [](QBrowserWindow *w) {
    //        qDebug() << w->size();
    //        qDebug("++++++++++++++++++++++++++++++++++++++++++++++++");
    //    });
}

void WindowManager::addWindowNotInFocus(QString url)
{
}

void WindowManager::removeWindow(int windowId)
{
    if (mp.count(windowId)) {
        auto closing_window = mp[windowId];
        mp.erase(windowId);
        if (windowId == currentWindowId && !mp.empty()) {
                toggleTab(mp.cbegin()->first);
        }

        closing_window->setVisible(false);
        if (mp.empty()) {
            closing_window->parent()->setVisible(false);
        }

        closing_window->setParent(nullptr);
        closing_window->close();
        emit removeTab(windowId);
    }
}

void WindowManager::resizeWindow(int width, int height)
{
    for (auto &&[_, w] : mp)
        w->resize(width, height);
}

void WindowManager::addWindow(QBrowserWindow *new_window)
{
    new_window->show();
    new_window->setFramePosition({0, 74});
    int id = new_window->getBrowserId();
    mp.insert({id, new_window});
    emit addTab(id, "Loading...", "Loading...", "", true);
}

void WindowManager::tabStateChanged(int windowId, const QString &title, const QString &url, const QString &icon)
{
    emit setTabState(windowId, title, url, icon);

    if (title != "" && url != "" && icon != "") {
        emit addHistory(title, url);
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

void WindowManager::initWindow(QString url)
{
    addWindow(url);
    emit addTab(-1, "", "", "", true);
}
