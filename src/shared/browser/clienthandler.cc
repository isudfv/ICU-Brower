//
// Created by liang on 22-4-19.
//

#include <iostream>
#include <QDebug>
#include "include/cef_base.h"
#include "include/cef_app.h"
#include "include/cef_parser.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"

#include "clienthandler.h"
namespace {

// Custom menu command Ids.
enum client_menu_ids {
  CLIENT_ID_SHOW_DEVTOOLS = MENU_ID_USER_FIRST,
  CLIENT_ID_CLOSE_DEVTOOLS,
  CLIENT_ID_INSPECT_ELEMENT,
  CLIENT_ID_SHOW_SSL_INFO,
  CLIENT_ID_CURSOR_CHANGE_DISABLED,
  CLIENT_ID_OFFLINE,
  CLIENT_ID_TESTMENU_SUBMENU,
  CLIENT_ID_TESTMENU_CHECKITEM,
  CLIENT_ID_TESTMENU_RADIOITEM1,
  CLIENT_ID_TESTMENU_RADIOITEM2,
  CLIENT_ID_TESTMENU_RADIOITEM3,
};

// Returns a data: URI with the specified contents.
std::string GetDataURI(const std::string &data, const std::string &mime_type) {
  return "data:" + mime_type + ";base64," +
      CefURIEncode(CefBase64Encode(data.data(), data.size()), false)
          .ToString();
}

void SetBrowserZoom(CefRefPtr<CefBrowser> browser, double delta) {
  browser->GetHost()->SetZoomLevel(browser->GetHost()->GetZoomLevel() + delta);
}

}  // namespace

bool ClientHandler::OnBeforePopup(CefRefPtr<CefBrowser> browser,
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
                                  bool *no_javascript_access) {

  CEF_REQUIRE_UI_THREAD();

  if (delegate_) {
    delegate_->OnBeforeBrowserPopup(windowInfo);
  }
  return false;
}
void ClientHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();

  if (delegate_)
    delegate_->OnBrowserCreated(browser);
}
bool ClientHandler::DoClose(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();
  if (delegate_) {
    delegate_->OnDoBrowserClose(browser);
  }
  return false;
}

void ClientHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();

  if (delegate_) {
    delegate_->OnBrowserClosed(browser);
  }
}

void ClientHandler::OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
                                        CefRefPtr<CefFrame> frame,
                                        CefRefPtr<CefContextMenuParams> params,
                                        CefRefPtr<CefMenuModel> model) {
  CEF_REQUIRE_UI_THREAD();

  if ((params->GetTypeFlags() & (CM_TYPEFLAG_PAGE | CM_TYPEFLAG_FRAME)) != 0) {
    // Add a separator if the menu already has items.
    if (model->GetCount() > 0)
      model->AddSeparator();

    model->AddItem(CLIENT_ID_SHOW_DEVTOOLS, "&Show DevTools");
    model->AddItem(CLIENT_ID_CLOSE_DEVTOOLS, "Close DevTools");
    model->AddSeparator();
    model->AddItem(CLIENT_ID_INSPECT_ELEMENT, "Inspect Element");
  }
}

bool ClientHandler::OnContextMenuCommand(CefRefPtr<CefBrowser> browser,
                                         CefRefPtr<CefFrame> frame,
                                         CefRefPtr<CefContextMenuParams> params,
                                         int command_id,
                                         CefContextMenuHandler::EventFlags event_flags) {
  CEF_REQUIRE_UI_THREAD();

  switch (command_id) {
    case CLIENT_ID_SHOW_DEVTOOLS:OnShowDevTools(browser, CefPoint(0, 0));
      return true;
    case CLIENT_ID_CLOSE_DEVTOOLS:browser->GetHost()->CloseDevTools();
      return true;
    case CLIENT_ID_INSPECT_ELEMENT:OnShowDevTools(browser, CefPoint(params->GetXCoord(), params->GetYCoord()));
      return true;
    default:return false;
  }
}

void ClientHandler::OnLoadError(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                CefLoadHandler::ErrorCode errorCode,
                                const CefString &errorText,
                                const CefString &failedUrl) {
  CEF_REQUIRE_UI_THREAD();


  // Don't display an error for downloaded files.
  if (errorCode == ERR_ABORTED)
    return;

  // Display a load error message using a data: URI.
  std::stringstream ss;
  ss << "<html><body bgcolor=\"white\">"
        "<h2>Failed to load URL "
     << std::string(failedUrl) << " with error " << std::string(errorText)
     << " (" << errorCode << ").</h2></body></html>";

  frame->LoadURL(GetDataURI(ss.str(), "text/html"));
}

void ClientHandler::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString &title) {
  if (delegate_) {
    delegate_->OnSetTitle(browser, title);
  }
}

bool ClientHandler::OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
                                  const CefKeyEvent &event,
                                  CefEventHandle os_event,
                                  bool *is_keyboard_shortcut) {
  if (event.modifiers == EVENTFLAG_CONTROL_DOWN) {
    if (event.type == KEYEVENT_RAWKEYDOWN) {
      switch (event.native_key_code) {
        case 20:SetBrowserZoom(browser, -0.5);
          return true;
        case 21:SetBrowserZoom(browser, +0.5);
          return true;
        default:return false;
      }
    }
  } else if (event.type == KEYEVENT_RAWKEYDOWN) {
    std::cout << event.native_key_code << std::endl;
    switch (event.native_key_code) {
      case 71:browser->Reload();
        return true;
    }
  }

  return false;
}

void ClientHandler::OnShowDevTools(CefRefPtr<CefBrowser> browser, const CefPoint &inspect_element_at) {
  CefWindowInfo window_info;
  CefRefPtr<CefBrowserHost> host = browser->GetHost();
  CefRefPtr<CefClient> client = browser->GetHost()->GetClient();
  CefBrowserSettings browser_settings;

  if (!host->HasDevTools()) {
    delegate_->OnBeforeBrowserPopup(window_info);
  }

  host->ShowDevTools(window_info, client, browser_settings, inspect_element_at);
}

void ClientHandler::OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString &url) {
  CEF_REQUIRE_UI_THREAD();
  if (frame->IsMain())
    delegate_->OnSetAddress(browser, url);
}

void ClientHandler::OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
                                         bool isLoading,
                                         bool canGoBack,
                                         bool canGoForward) {
  CEF_REQUIRE_UI_THREAD();
  delegate_->OnSetLoadingState(browser, isLoading, canGoBack, canGoForward);
}
bool ClientHandler::OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   CefRefPtr<CefRequest> request,
                                   bool user_gesture,
                                   bool is_redirect) {
  return false;
}
bool ClientHandler::OnOpenURLFromTab(CefRefPtr<CefBrowser> browser,
                                     CefRefPtr<CefFrame> frame,
                                     const CefString &target_url,
                                     CefRequestHandler::WindowOpenDisposition target_disposition,
                                     bool user_gesture) {
  if (target_disposition == WOD_NEW_BACKGROUND_TAB ||
      target_disposition == WOD_NEW_FOREGROUND_TAB) {

    delegate_->OnCreateBrowserByUrl(target_url);

    return true;
  }

  return false;
}
void ClientHandler::OnBeforeDownload(CefRefPtr<CefBrowser> browser,
                                     CefRefPtr<CefDownloadItem> download_item,
                                     const CefString &suggested_name,
                                     CefRefPtr<CefBeforeDownloadCallback> callback) {
  CEF_REQUIRE_UI_THREAD();

  if (delegate_) delegate_->OnStartDownload(download_item, suggested_name, callback);
}

void ClientHandler::OnDownloadUpdated(CefRefPtr<CefBrowser> browser,
                                      CefRefPtr<CefDownloadItem> download_item,
                                      CefRefPtr<CefDownloadItemCallback> callback) {
  CEF_REQUIRE_UI_THREAD();

  if (delegate_) delegate_->OnUpdateDownloadState(download_item, callback);
}

CefResourceRequestHandler::ReturnValue ClientHandler::OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser,
                                                                           CefRefPtr<CefFrame> frame,
                                                                           CefRefPtr<CefRequest> request,
                                                                           CefRefPtr<CefCallback> callback) {
  CEF_REQUIRE_IO_THREAD();

  if (delegate_) {
    if (delegate_->CheckRequestIntercept(request)) {
      qDebug() << "BLOCKING";
      return RV_CANCEL;
    }
  }
  return RV_CONTINUE;
}
