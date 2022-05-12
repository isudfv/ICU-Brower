//
// Created by liang on 22-4-20.
//

#include "browserclient.h"
#include "cef_app.h"
#include "browserprofile.h"

#include <mutex>
#include <fstream>

namespace {
std::mutex window_lock;
QBrowserWindow *curr_window;
char *ad_block_buffer;
} // namespace

BrowserClient::BrowserClient() {
  handler_ = new ClientHandler(this);
  InitAdBlockClient();
}

void BrowserClient::OnBrowserCreated(CefRefPtr<CefBrowser> browser) {
  // Add to the list of existing browsers.

  curr_window->setBrowserId(browser->GetIdentifier());
  browser_list_[browser->GetIdentifier()] = {curr_window, browser};
  curr_window->show();
  window_lock.unlock();
}

void BrowserClient::OnBeforeBrowserPopup(CefWindowInfo &window_info) {
  window_lock.lock();

  auto *w = new QBrowserWindow;
  curr_window = w;

#ifdef __linux__
  window_info.SetAsChild(w->winId(), {0, 0, 0, 0});
#endif

#ifdef _WINDOWS
  window_info.SetAsChild((HWND)w->winId(), {0, 0, 0, 0});
#endif
}

void BrowserClient::OnSetTitle(CefRefPtr<CefBrowser> browser, const CefString &title) {
  browser_list_[browser->GetIdentifier()].first->setTitle(QString::fromStdString(title.ToString()));
}

void BrowserClient::OnSetAddress(CefRefPtr<CefBrowser> browser, const CefString &url) {
  browser_list_[browser->GetIdentifier()].first->setBrowserUrl(QString::fromStdString(url.ToString()));
}

void BrowserClient::OnSetLoadingState(CefRefPtr<CefBrowser> browser,
                                      bool isLoading,
                                      bool canGoBack,
                                      bool canGoForward) {
  browser_list_[browser->GetIdentifier()].first->setLoadingState(isLoading, canGoBack, canGoForward);
}

void BrowserClient::CreateBrowser(QBrowserWindow *target_window, const CefString &url) {
  window_lock.lock();
  CefWindowInfo window_info;

#ifdef __linux__
  window_info.SetAsChild(target_window->winId(), {0, 0, 0, 0});
#endif

#ifdef _WINDOWS
  window_info.SetAsPopup(nullptr, "sdf");
  window_info.SetAsChild((HWND)target_window->winId(), {0, 0, 0, 0});
#endif

  curr_window = target_window;

  CefBrowserSettings browser_settings;

  CefBrowserHost::CreateBrowser(window_info,
                                handler_,
                                url,
                                browser_settings,
                                nullptr,
                                nullptr);
}

BrowserClient *BrowserClient::GetInstance() {
  static BrowserClient instance;
  return &instance;
}

void BrowserClient::OnCreateBrowserByUrl(const CefString &url) {
  QBrowserWindow *new_window = new QBrowserWindow(url);
}

void BrowserClient::OnStartDownload(CefRefPtr<CefDownloadItem> download_item,
                                    const CefString &suggested_name,
                                    CefRefPtr<CefBeforeDownloadCallback> callback) {
  auto t = download_item_list_[download_item->GetId()].first;

  qDebug() << download_item->IsInProgress() << download_item->IsComplete()
           << download_item->IsCanceled() << download_item->IsValid();
  qDebug() << 21234132;

  auto full_path = GetDownloadPath(suggested_name);

  t->setFileName(QString::fromStdString(suggested_name.ToString()));
  t->setFullPath(QString::fromStdString(full_path.ToString()));

  qDebug() << QString::fromStdString(full_path.ToString());

  callback->Continue(full_path, false);
}

void BrowserClient::OnUpdateDownloadState(CefRefPtr<CefDownloadItem> download_item,
                                          CefRefPtr<CefDownloadItemCallback> callback) {
  QDownloadWidget *download_widget;
  if (download_item_list_.find(download_item->GetId()) == download_item_list_.end()) {
    QDownloadWidget *t = new QDownloadWidget(download_item->GetId(), nullptr);
    download_item_list_[download_item->GetId()] = {t, download_item};
    download_widget = t;
  } else {
    download_widget = download_item_list_[download_item->GetId()].first;
  }

  download_widget->setDownloadStatus(
      QDateTime::fromSecsSinceEpoch(download_item->GetStartTime().GetTimeT()),
      download_item->GetPercentComplete());

  if (download_item->IsComplete()) download_item_list_.erase(download_item->GetId());
}

CefString BrowserClient::GetDownloadPath(const CefString &suggested_name) {
  std::string download_directory = "/home/liang/";
  return download_directory + suggested_name.ToString();
}

void BrowserClient::DoBrowserLoadUrl(int browser_id, const QString &url) {
  browser_list_[browser_id].second->GetMainFrame()->LoadURL(url.toStdString());
}

void BrowserClient::DoBrowserReload(int browser_id) {
  browser_list_[browser_id].second->Reload();
}

void BrowserClient::DoBrowserStopLoad(int browser_id) {
  browser_list_[browser_id].second->StopLoad();
}

void BrowserClient::DoBrowserGoBack(int browser_id) {
  browser_list_[browser_id].second->GoBack();
}

void BrowserClient::DoBrowserGoForward(int browser_id) {
  browser_list_[browser_id].second->GoForward();
}

void BrowserClient::TryCloseBrowser(int browser_id) {
  browser_list_[browser_id].second->GetHost()->TryCloseBrowser();
}

CefWindowHandle BrowserClient::GetBrowserWindowHanlder(int browser_id) {
  return browser_list_[browser_id].second->GetHost()->GetWindowHandle();
}

void BrowserClient::OnDoBrowserClose(CefRefPtr<CefBrowser> browser) {
  browser_list_[browser->GetIdentifier()].first->setClosingState(true);
  browser_list_[browser->GetIdentifier()].first->close();
}

void BrowserClient::OnBrowserClosed(CefRefPtr<CefBrowser> browser) {
  browser_list_[browser->GetIdentifier()].second = nullptr;
  browser_list_.erase(browser->GetIdentifier());

  if (browser_list_.empty()) CefQuitMessageLoop();
}
bool BrowserClient::CheckRequestIntercept(CefRefPtr<CefRequest> request) {

  request->SetHeaderByName("User-Agent",
                           BrowserProfile::GetInstance()->GetUserAgent(),
                           true);

  if (BrowserProfile::GetInstance()->IsAdBlockFlag()
      && ad_block_client_.matches(request->GetURL().ToString().c_str(),
                                  FONoFilterOption,
                                  request->GetReferrerURL().ToString().c_str())) {
    return true;
  }
  return false;
}

void BrowserClient::InitAdBlockClient() {
  // load ad-blocker dat file
  std::fstream in("ABPFilterParserData.dat", std::ios::in | std::ios::out);
  if (in) {
    in.seekg(0, std::ios::end);
    auto len = in.tellg();
    ad_block_buffer = new char[len];
    in.seekg(0, std::ios::beg);
    in.read(ad_block_buffer, len);
    in.close();

    ad_block_client_.deserialize(ad_block_buffer);
  }
}

BrowserClient::~BrowserClient() {
  delete[]ad_block_buffer;
}
