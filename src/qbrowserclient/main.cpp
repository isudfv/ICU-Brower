#include <iostream>
#include <QApplication>
#include "browserclient.h"
#include "browserprofile.h"
#include "clienthandler.h"
#include "qbrowserwindow.h"

int main(int argc, char **argv) {
  BrowserProfile::InitFromCommandLine(argc, argv);

  QApplication a(argc, argv);

  BrowserProfile::RunBrowser();

  BrowserProfile::ShutdownBrowser();
}