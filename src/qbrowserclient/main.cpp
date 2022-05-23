#include <QApplication>
#include "browserprofile.h"
#include "qbrowserwindow.h"

int main(int argc, char **argv) {
  BrowserProfile::InitFromCommandLine(argc, argv);

  QApplication a(argc, argv);

  QBrowserWindow w("bilibili.com");

  BrowserProfile::RunBrowser();

  BrowserProfile::ShutdownBrowser();
}