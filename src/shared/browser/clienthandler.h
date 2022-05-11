//
// Created by liang on 22-4-19.
//

#ifndef QBROWSERCLIENT__CLIENTHANDLER_H_
#define QBROWSERCLIENT__CLIENTHANDLER_H_

#include "include/cef_client.h"

class ClientHandler :
    public CefClient,
    public CefDisplayHandler,
    public CefDownloadHandler,
    public CefKeyboardHandler,
    public CefContextMenuHandler,
    public CefRequestHandler,
    public CefResourceRequestHandler,
    public CefFrameHandler,
    public CefLifeSpanHandler,
    public CefLoadHandler {
 public:
  class Delegate {
   public:
    virtual bool CheckRequestIntercept(CefRefPtr<CefRequest> request) = 0;

    virtual void OnBrowserCreated(CefRefPtr<CefBrowser> browser) = 0;

    virtual void OnBeforeBrowserPopup(CefWindowInfo &windowInfo) = 0;

    virtual void OnSetAddress(CefRefPtr<CefBrowser> browser, const CefString &url) = 0;

    virtual void OnSetTitle(CefRefPtr<CefBrowser> browser, const CefString &title) = 0;

    virtual void OnStartDownload(CefRefPtr<CefDownloadItem> download_item,
                                 const CefString &suggested_name,
                                 CefRefPtr<CefBeforeDownloadCallback> callback) = 0;

    virtual void OnUpdateDownloadState(CefRefPtr<CefDownloadItem> download_item,
                                       CefRefPtr<CefDownloadItemCallback> callback) = 0;

//    // Called when the browser is closing.
//    virtual void OnBrowserClosing(CefRefPtr<CefBrowser> browser) = 0;
//
//    // Called when the browser has been closed.
    virtual void OnDoBrowserClose(CefRefPtr<CefBrowser> browser) = 0;

    virtual void OnBrowserClosed(CefRefPtr<CefBrowser> browser) = 0;

    virtual void OnCreateBrowserByUrl(const CefString &url) = 0;

//    // Set the window URL address.
//    virtual void OnSetAddress(const std::string& url) = 0;
//
//    // Set the window title.
//    virtual void OnSetTitle(const std::string& title) = 0;
//
//    // Set fullscreen mode.
//    virtual void OnSetFullscreen(bool fullscreen) = 0;
//
//    // Auto-resize contents.
//    virtual void OnAutoResize(const CefSize& new_size) = 0;
//
    // Set the loading state.
    virtual void OnSetLoadingState(CefRefPtr<CefBrowser> browser,
                                   bool isLoading,
                                   bool canGoBack,
                                   bool canGoForward) = 0;

   protected:
    virtual ~Delegate() = default;
  };

  explicit ClientHandler(Delegate *delegate) {
    this->delegate_ = delegate;
  }

  // CefClient methods:
  CefRefPtr<CefDownloadHandler> GetDownloadHandler() override {
    return this;
  }

  CefRefPtr<CefDisplayHandler> GetDisplayHandler() override {
    return this;
  }

  CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override {
    return this;
  }

  CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() override {
    return this;
  }

  CefRefPtr<CefLoadHandler> GetLoadHandler() override {
    return this;
  }

  CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() override {
    return this;
  }

  CefRefPtr<CefRequestHandler> GetRequestHandler() override {
    return this;
  }

  CefRefPtr<CefFrameHandler> GetFrameHandler() override { return this; }

  CefRefPtr<CefResourceRequestHandler> GetResourceRequestHandler(CefRefPtr<CefBrowser> browser,
                                                                 CefRefPtr<CefFrame> frame,
                                                                 CefRefPtr<CefRequest> request,
                                                                 bool is_navigation,
                                                                 bool is_download,
                                                                 const CefString &request_initiator,
                                                                 bool &disable_default_handling) override {
    return this;
  }

  ReturnValue OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   CefRefPtr<CefRequest> request,
                                   CefRefPtr<CefCallback> callback) override;

  // LifeSpanHandler
  bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
                     CefRefPtr<CefFrame> frame,
                     const CefString &target_url,
                     const CefString &target_frame_name,
                     CefLifeSpanHandler::WindowOpenDisposition target_disposition,
                     bool user_gesture,
                     const CefPopupFeatures &popupFeatures,
                     CefWindowInfo &windowInfo,
                     CefRefPtr<CefClient> &client,
                     CefBrowserSettings &settings,
                     CefRefPtr<CefDictionaryValue> &extra_info,
                     bool *no_javascript_access) override;
  void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
  bool DoClose(CefRefPtr<CefBrowser> browser) override;
  void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

  // CefContextMenuHandler methods
  void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           CefRefPtr<CefContextMenuParams> params,
                           CefRefPtr<CefMenuModel> model) override;
  bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser,
                            CefRefPtr<CefFrame> frame,
                            CefRefPtr<CefContextMenuParams> params,
                            int command_id,
                            EventFlags event_flags) override;

  // CefLoadHandler methods:
  void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
                            bool isLoading,
                            bool canGoBack,
                            bool canGoForward) override;
  void OnLoadError(CefRefPtr<CefBrowser> browser,
                   CefRefPtr<CefFrame> frame,
                   ErrorCode errorCode,
                   const CefString &errorText,
                   const CefString &failedUrl) override;

  // CefDownloadHandler methods
  void OnBeforeDownload(CefRefPtr<CefBrowser> browser,
                        CefRefPtr<CefDownloadItem> download_item,
                        const CefString &suggested_name,
                        CefRefPtr<CefBeforeDownloadCallback> callback) override;
  void OnDownloadUpdated(CefRefPtr<CefBrowser> browser,
                         CefRefPtr<CefDownloadItem> download_item,
                         CefRefPtr<CefDownloadItemCallback> callback) override;

  // CefDisplayHandler methods:
  void OnAddressChange(CefRefPtr<CefBrowser> browser,
                       CefRefPtr<CefFrame> frame,
                       const CefString &url) override;
  void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString &title) override;

  // CefKeyboardHandler:
  bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
                             const CefKeyEvent &event,
                             CefEventHandle os_event,
                             bool *is_keyboard_shortcut) override;

  // CefRequestHandler methods
  bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
                      CefRefPtr<CefFrame> frame,
                      CefRefPtr<CefRequest> request,
                      bool user_gesture,
                      bool is_redirect) override;
  bool OnOpenURLFromTab(
      CefRefPtr<CefBrowser> browser,
      CefRefPtr<CefFrame> frame,
      const CefString &target_url,
      CefRequestHandler::WindowOpenDisposition target_disposition,
      bool user_gesture) override;

  void OnShowDevTools(CefRefPtr<CefBrowser> browser, const CefPoint &inspect_element_at);

  Delegate *delegate_;

// Include the default reference counting implementation.
 IMPLEMENT_REFCOUNTING(ClientHandler);
};

#endif //QBROWSERCLIENT__CLIENTHANDLER_H_