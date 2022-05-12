//
// Created by liang on 22-5-12.
//

#ifndef ICU_BROWSER_SRC_SHARED_PROFILE_BROWSERPROFILE_H_
#define ICU_BROWSER_SRC_SHARED_PROFILE_BROWSERPROFILE_H_

#include "cef_app.h"

class BrowserProfile {
 public:
  BrowserProfile();
  static BrowserProfile *GetInstance();

  void InitCefSettings(const CefSettings& settings);

  void SetAdBlockFlag(bool ad_block_flag);
  bool IsAdBlockFlag() const;

  const CefString &GetUserAgent() const;
  void SetUserAgent(const CefString &user_agent);

 private:
  bool ad_block_flag_;
  CefString user_agent_;
};

#endif //ICU_BROWSER_SRC_SHARED_PROFILE_BROWSERPROFILE_H_
