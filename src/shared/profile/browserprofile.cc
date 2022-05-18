//
// Created by liang on 22-5-12.
//

#include <qbrowserwindow.h>
#include "browserprofile.h"
#include "cef_app.h"

BrowserProfile *BrowserProfile::GetInstance()
{
    static BrowserProfile instance;
    return &instance;
}

bool BrowserProfile::IsAdBlockFlag() const
{
    return ad_block_flag_;
}

void BrowserProfile::SetAdBlockFlag(bool ad_block_flag)
{
    ad_block_flag_ = ad_block_flag;
}

BrowserProfile::BrowserProfile()
{
    ad_block_flag_ = true;
//  user_agent_ = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.88 Safari/537.36";

    user_agent_ = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.88 Safari/537.36";
//  user_agent_ = "CEF";
}

const QString &BrowserProfile::GetUserAgent() const
{
    return user_agent_;
}

void BrowserProfile::SetUserAgent(const QString &user_agent)
{
    user_agent_ = user_agent;
}

int BrowserProfile::InitFromCommandLine(int argc, char **argv)
{
#ifdef __linux__
    CefMainArgs main_args(argc, argv);
#endif
#ifdef _WINDOWS
    HINSTANCE h = GetModuleHandle(nullptr);
    CefMainArgs main_args(h);
#endif

    // CEF applications have multiple sub-processes (render, GPU, etc) that share
    // the same executable. This function checks the command-line and, if this is
    // a sub-process, executes the appropriate logic.
    int exit_code = CefExecuteProcess(main_args, nullptr, nullptr);
    if (exit_code >= 0) {
        // The sub-process has completed so return here.
        return exit_code;
    }

    // Parse command-line arguments for use in this method.
    CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();

#ifdef __linux__
    command_line->InitFromArgv(argc, argv);
#endif
#ifdef _WINDOWS
#endif

    // Specify CEF global settings here.
    CefSettings settings;

    CefRefPtr<CefApp> app;

    CefInitialize(main_args, settings, app.get(), nullptr);

    return 0;
}

const QString &BrowserProfile::GetMainPageUrl() const
{
    return main_page_url_;
}

void BrowserProfile::SetMainPageUrl(const QString &main_page_url)
{
    main_page_url_ = main_page_url;
}

void BrowserProfile::RunBrowser()
{
    QBrowserWindow w(GetInstance()->main_page_url_);
    CefRunMessageLoop();
}

void BrowserProfile::ShutdownBrowser()
{
    CefShutdown();
}
