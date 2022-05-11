//
// Created by liang on 22-5-11.
//

#include "ad_block_client.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

string getFileContents(const char *filename)
{
  fstream in(filename, ios::in | ios::out);
  if (in) {
    ostringstream contents;
    contents << in.rdbuf();
    in.close();
    return(contents.str());
  }
  throw(errno);
}

void writeFile(const char *filename, const char *buffer, int length)
{
  ofstream outFile(filename, ios::out | ios::binary);
  if (outFile) {
    outFile.write(buffer, length);
    outFile.close();
    return;
  }
  throw(errno);
}


int main(int argc, char**argv) {
  std::string &&easyListTxt = getFileContents("easylist.txt");
  const char *urlsToCheck[] = {
      // ||pagead2.googlesyndication.com^$~object-subrequest
      "http://pagead2.googlesyndication.com/pagead/show_ads.js",
      // Should be blocked by: ||googlesyndication.com/safeframe/$third-party
      "http://tpc.googlesyndication.com/safeframe/1-0-2/html/container.html",
      // Should be blocked by: ||googletagservices.com/tag/js/gpt_$third-party
      "http://www.googletagservices.com/tag/js/gpt_mobile.js",
      // Shouldn't be blocked
      "http://www.brianbondy.com"
  };

  // This is the site who's URLs are being checked, not the domain of the URL being checked.
  const char *currentPageDomain = "slashdot.org";

  // Parse easylist
  AdBlockClient client;
  client.parse(easyListTxt.c_str());

  // Do the checks
  std::for_each(urlsToCheck, urlsToCheck + sizeof(urlsToCheck) / sizeof(urlsToCheck[0]), [&client, currentPageDomain](std::string const &urlToCheck) {
    if (client.matches(urlToCheck.c_str(), FONoFilterOption, currentPageDomain)) {
      cout << urlToCheck << ": You should block this URL!" << endl;
    } else {
      cout << urlToCheck << ": You should NOT block this URL!" << endl;
    }
  });

  int size;
  // This buffer is allocate on the heap, you must call delete[] when you're done using it.
  char *buffer = client.serialize(&size);
  writeFile("./ABPFilterParserData.dat", buffer, size);

  AdBlockClient client2;
  // Deserialize uses the buffer directly for subsequent matches, do not free until all matches are done.
  client2.deserialize(buffer);
  // Prints the same as client.matches would
  std::for_each(urlsToCheck, urlsToCheck + sizeof(urlsToCheck) / sizeof(urlsToCheck[0]), [&client2, currentPageDomain](std::string const &urlToCheck) {
    if (client2.matches(urlToCheck.c_str(), FONoFilterOption, currentPageDomain)) {
      cout << urlToCheck << ": You should block this URL!" << endl;
    } else {
      cout << urlToCheck << ": You should NOT block this URL!" << endl;
    }
  });
  delete[] buffer;
  return 0;
}