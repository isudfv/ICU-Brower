#include <QApplication>
#include "browserprofile.h"
#include "qbrowserwindow.h"

int main(int argc, char **argv) {
  BrowserProfile::InitFromCommandLine(argc, argv);

  QApplication a(argc, argv);

  QBrowserWindow w("https://mirror.tuna.tsinghua.edu.cn/ubuntu-releases/22.04/");

  BrowserProfile::RunBrowser();

  BrowserProfile::ShutdownBrowser();
}