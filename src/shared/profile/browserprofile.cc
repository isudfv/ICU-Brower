//
// Created by liang on 22-5-12.
//

#include "browserprofile.h"
BrowserProfile *BrowserProfile::GetInstance() {
  static BrowserProfile instance;
  return &instance;
}

bool BrowserProfile::IsAdBlockFlag() const {
  return ad_block_flag_;
}

void BrowserProfile::SetAdBlockFlag(bool ad_block_flag) {
  ad_block_flag_ = ad_block_flag;
}

const CefString &BrowserProfile::GetUserAgent() const {
  return user_agent_;
}

void BrowserProfile::SetUserAgent(const CefString &user_agent) {
  user_agent_ = user_agent;
}

BrowserProfile::BrowserProfile() {
  ad_block_flag_ = true;
  user_agent_ = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.88 Safari/537.36";
}

void BrowserProfile::InitCefSettings(const CefSettings &settings) {
//  CefString(&settings.user_agent) = user_agent_;
}
