#include <iostream>
#include <QApplication>
#include "browserclient.h"
#include "browserprofile.h"
#include "clienthandler.h"
#include "qbrowserwindow.h"
#include "cef_app.h"

int main(int argc, char **argv) {
  // Provide CEF with command-line arguments.

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

  BrowserProfile::GetInstance()->InitCefSettings(settings);

  CefRefPtr<CefApp> app;

  CefInitialize(main_args, settings, app.get(), nullptr);
  QApplication a(argc, argv);

  QBrowserWindow w("https://www.ypojie.com/");

  CefRunMessageLoop();

  CefShutdown();

//  return a.exec();
}