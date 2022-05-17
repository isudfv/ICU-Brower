#include "windowmanager.h"
#include "historymanager.h"

void WindowManager::toggleTab(int windowId)
{
//    if(mp.count(currentWindowId)) mp[currentWindowId]->hide();
//    currentWindowId = windowId;
//    mp[currentWindowId]->show();
    bool activeBack = true;
    bool activeForward = true;//获取状态

    emit setHeaderState(activeBack, activeForward);
}

void WindowManager::doGoBack(int windowId)
{
//    mp[windowId]->doGoBack();
    bool activeBack = true;
    bool activeForward = true;
    QString currentUrl = "GoBack";//获取状态
    emit setTabState(windowId, currentUrl, currentUrl, "qrc:/icons/stackoverflow.svg");
    emit setHeaderState(activeBack, activeForward);
}

void WindowManager::doGoForward(int windowId)
{
//    mp[windowId]->doGoBack();
    bool activeBack = true;
    bool activeForward = true;
    QString currentUrl = "GoForWard";//获取状态
    emit setTabState(windowId, currentUrl, currentUrl, "qrc:/icons/stackoverflow.svg");
    emit setHeaderState(activeBack, activeForward);
}

void WindowManager::doReLoad(int windowId)
{
//    mp[windowId]->doReload();
    bool activeBack = true;
    bool activeForward = true;
    QString currentTitle = "ReLoad";//获取状态

    emit setTabState(windowId, currentTitle, currentTitle, "qrc:/icons/stackoverflow.svg");
    emit setHeaderState(activeBack, activeForward);
}

void WindowManager::doLoadUrl(int windowId, QString url, int uid)
{
//    mp[windowId]->doLoadUrl(url);
    bool activeBack = true;
    bool activeForward = true;
    QString currentTitle = url;//获取状态
//    HistoryManager::getInstanse()->addHistory(currentTitle, url, uid);
    emit setTabState(windowId, currentTitle, url, "qrc:/icons/stackoverflow.svg");
    emit setHeaderState(activeBack, activeForward);
}

void WindowManager::addWindow(QString url)
{
   QBrowserWindow *w = new QBrowserWindow(url);
}

void WindowManager::addWindowNotInFocus(QString url)
{

}

void WindowManager::removeWindow(int windowId)
{
    //~mp[windowId]
    mp.erase(windowId);
    emit removeTab(windowId);
}

int WindowManager::getIndex()
{
    for (int i = 0; i < INT_MAX; ++i) {
        if (mp.count(i) == 0) {
            return i;
        }
    }
    return -1;
}

void WindowManager::addWindow(QBrowserWindow *new_window)
{
    int id = getIndex();
    mp.insert({id, new_window});
    QString icon = "qrc:/icons/stackoverflow.svg";
    emit addTab(id, "", "", icon, true);
    //    if(mp.count(currentWindowId)) mp[currentWindowId]->hide();
    //    currentWindowId = id;
    //    mp[currentWindowId]->show();
//    bool activeBack = true;
//    bool activeForward = true;;//获取状态
//    emit setHeaderState(activeBack, activeForward);

    qDebug() << "Add Windows";
}
