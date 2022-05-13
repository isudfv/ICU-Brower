//
// Created by liang on 22-4-20.
//

#ifndef BROWSERCLIENT__BROWSERCLIENT_H_
#define BROWSERCLIENT__BROWSERCLIENT_H_

#include "clienthandler.h"
#include "qbrowserwindow.h"
#include "downloaditem.h"
#include "ad_block_client.h"

class BrowserClient : public ClientHandler::Delegate {
 public:
  explicit BrowserClient();

//  impl the SimpleHandler::Delegate

  bool CheckRequestIntercept(CefRefPtr<CefRequest> request) override;

  void OnBrowserCreated(CefRefPtr<CefBrowser> browser) override;

  void OnBeforeBrowserPopup(CefWindowInfo &windowInfo) override;

  void OnDoBrowserClose(CefRefPtr<CefBrowser> browser) override;

  void OnBrowserClosed(CefRefPtr<CefBrowser> browser) override;

  void OnSetAddress(CefRefPtr<CefBrowser> browser, const CefString &url) override;

  void OnSetTitle(CefRefPtr<CefBrowser> browser, const CefString &title) override;

  void OnCreateBrowserByUrl(const CefString &url) override;

  void OnSetLoadingState(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward) override;

  void OnStartDownload(CefRefPtr<CefDownloadItem> download_item,
                       const CefString &suggested_name,
                       CefRefPtr<CefBeforeDownloadCallback> callback) override;

  void OnUpdateDownloadState(CefRefPtr<CefDownloadItem> download_item,
                             CefRefPtr<CefDownloadItemCallback> callback) override;

  // QBrowserWindow user method
  void CreateBrowser(QBrowserWindow *target_window, const CefString &url);

  void TryCloseBrowser(int browser_id);

  CefWindowHandle GetBrowserWindowHandler(int browser_id);

  void DoBrowserLoadUrl(int browser_id, const QString &url);

  void DoBrowserReload(int browser_id);

  void DoBrowserStopLoad(int browser_id);

  void DoBrowserGoBack(int browser_id);

  void DoBrowserGoForward(int browser_id);

  static BrowserClient *GetInstance();

  BrowserClient(const BrowserClient &) = delete;
  ~BrowserClient() override;
  const BrowserClient &operator=(const BrowserClient &) = delete;

 private:
  ClientHandler *handler_;

  AdBlockClient ad_block_client_;

  std::unordered_map<int, std::pair<QBrowserWindow *, CefRefPtr<CefBrowser>>> browser_list_;

  std::unordered_map<DownloadItem::Id, std::pair<DownloadItem *, CefRefPtr<CefDownloadItem>>> download_item_list_;

  void InitAdBlockClient();
};

#endif //BROWSERCLIENT__BROWSERCLIENT_H_