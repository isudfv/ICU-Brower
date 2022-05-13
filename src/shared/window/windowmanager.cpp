#include "windowmanager.h"

void WindowManager::toggleTab(int windowId){
//    if(mp.count(currentWindowId)) mp[currentWindowId]->hide();
//    currentWindowId = windowId;
//    mp[currentWindowId]->show();
    bool activeBack = true;
    bool activeForward = true;//获取状态

    emit setHeaderState(activeBack,activeForward);
}

void WindowManager::doGoBack(int windowId,QJSValue callback){
//    mp[windowId]->doGoBack();
    bool activeBack = true;
    bool activeForward = true;
    QString currentUrl = "GoBack";//获取状态

    QJSValue title(currentUrl);
    QJSValue url_(currentUrl);
    QJSValue icon_("qrc:/icons/stackoverflow.svg");
    QJSValueList list;
    list.append(title);
    list.append(url_);
    list.append(icon_);
    callback.call(list);
    emit setHeaderState(activeBack,activeForward);
}

void WindowManager::doGoForward(int windowId,QJSValue callback){
//    mp[windowId]->doGoBack();
    bool activeBack = true;
    bool activeForward = true;
    QString currentUrl = "GoForWard";//获取状态

    QJSValue title(currentUrl);
    QJSValue url_(currentUrl);
    QJSValue icon_("qrc:/icons/stackoverflow.svg");
    QJSValueList list;
    list.append(title);
    list.append(url_);
    list.append(icon_);
    callback.call(list);
    emit setHeaderState(activeBack,activeForward);
}

void WindowManager::doReLoad(int windowId,QJSValue callback){
//    mp[windowId]->doReload();
    bool activeBack = true;
    bool activeForward = true;
    QString currentUrl = "ReLoad";//获取状态

    QJSValue title(currentUrl);
    QJSValue url_(currentUrl);
    QJSValue icon_("qrc:/icons/stackoverflow.svg");
    QJSValueList list;
    list.append(title);
    list.append(url_);
    list.append(icon_);
    callback.call(list);
    emit setHeaderState(activeBack,activeForward);
}

void WindowManager::doLoadUrl(int windowId,QString url,QJSValue callback){
//    mp[windowId]->doLoadUrl(url);
    bool activeBack = true;
    bool activeForward = true;
    QString currentTitle = url;//获取状态
    QJSValue title(currentTitle);
    QJSValue url_(url);
    QJSValue icon_("qrc:/icons/stackoverflow.svg");
    QJSValueList list;
    list.append(title);
    list.append(url_);
    list.append(icon_);
    callback.call(list);
    emit setHeaderState(activeBack,activeForward);
}

void WindowManager::addWindow(QString url){
//    Qwindow* newWindow =
    int id = getIndex();
//    mp.insert({id,newWindow});
    mp.insert({id,nullptr});
    QString title = url;//获取标题
    QString icon = "qrc:/icons/stackoverflow.svg";
    emit addTab(id,title,url,icon,true);
    //    if(mp.count(currentWindowId)) mp[currentWindowId]->hide();
    //    currentWindowId = id;
    //    mp[currentWindowId]->show();
    bool activeBack = true;
    bool activeForward = true;;//获取状态
    emit setHeaderState(activeBack,activeForward);

}

void WindowManager::addWindowNotInFocus(QString url){

}

void WindowManager::removeWindow(int windowId){
    //~mp[windowId]
    mp.erase(windowId);
    emit removeTab(windowId);
}

int WindowManager::getIndex(){
   for(int i =0;i < INT_MAX;++ i){
       if(mp.count(i) == 0) {
           return i;
       }
   }
   return -1;
}
