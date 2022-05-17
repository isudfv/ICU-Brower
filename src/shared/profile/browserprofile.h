//
// Created by liang on 22-5-12.
//

#ifndef ICU_BROWSER_SRC_SHARED_PROFILE_BROWSERPROFILE_H_
#define ICU_BROWSER_SRC_SHARED_PROFILE_BROWSERPROFILE_H_

#include <QString>

class BrowserProfile {
 public:
  BrowserProfile();
  static BrowserProfile *GetInstance();

  static int InitFromCommandLine(int argc, char **argv);

  static void RunBrowser();
  static void ShutdownBrowser();

  void SetAdBlockFlag(bool ad_block_flag);
  bool IsAdBlockFlag() const;

  const QString &GetUserAgent() const;
  void SetUserAgent(const QString &user_agent);

 private:
  QString user_agent_;

  bool ad_block_flag_;
  QString main_page_url_ = "chrome://version";

 public:
  const QString &GetMainPageUrl() const;
  void SetMainPageUrl(const QString &main_page_url);
};

#endif //ICU_BROWSER_SRC_SHARED_PROFILE_BROWSERPROFILE_H_