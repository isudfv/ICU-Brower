#include "windowmanager.h"

void WindowManager::toggleTab(int windowId){
//    mp[currentWindowId]->hide();
//    currentWindowId = windowId;
//    mp[currentWindowId]->show();
    bool activeBack = true;
    bool activeForward = true;
    QString currentUrl = "test";
    QString currentTitle = "test";//获取状态
    emit setState(activeBack,activeForward,currentUrl,currentTitle);
}

void WindowManager::doGoBack(int windowId){
//    mp[windowId]->doGoBack();
    bool activeBack = true;
    bool activeForward = true;
    QString currentUrl = "test";
    QString currentTitle = "test";//获取状态
    emit setState(activeBack,activeForward,currentUrl,currentTitle);
}

void WindowManager::doGoForward(int windowId){
//    mp[windowId]->doGoBack();
    bool activeBack = true;
    bool activeForward = true;
    QString currentUrl = "test";
    QString currentTitle = "test";//获取状态
    emit setState(activeBack,activeForward,currentUrl,currentTitle);
}

void WindowManager::doReLoad(int windowId){
//    mp[windowId]->doReload();
    bool activeBack = true;
    bool activeForward = true;
    QString currentUrl = "test";
    QString currentTitle = "test";//获取状态
    emit setState(activeBack,activeForward,currentUrl,currentTitle);
}

void WindowManager::doLoadUrl(int windowId,QString url,QJSValue callback){
//    mp[windowId]->doLoadUrl(url);
    bool activeBack = true;
    bool activeForward = true;
    QString currentUrl = url;
    QString currentTitle = url;//获取状态
    QJSValue title(currentTitle);
    QJSValueList list;
    list.append(title);
    callback.call(list);
    emit setState(activeBack,activeForward,currentUrl,currentTitle);
}

void WindowManager::addWindow(QString url){

}

void WindowManager::addWindowNotInFocus(QString url){

}

void WindowManager::removeWindow(int windowId){

}
