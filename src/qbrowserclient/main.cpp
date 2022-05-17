#include <QApplication>
#include "browserprofile.h"

int main(int argc, char **argv) {
  BrowserProfile::InitFromCommandLine(argc, argv);

  QApplication a(argc, argv);

  BrowserProfile::RunBrowser();

  BrowserProfile::ShutdownBrowser();
}