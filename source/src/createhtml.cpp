#include <createhtml.h>
#include <fsstream>
#include <iostream>
#include <string>
using namespace std;

const string headerTag = "!DOCTYPE html><html><head></head><body>";
const string footerTag = "</body></html>";

namespace FactoringCommonText {

void createHTMLForGivenText() {
  ofstream stream;
  ifstream inputFile("textfile", std::ios::binary | std::ios::ate);
  streamsize bufSize = file.tellg();
  inputFile.seekg(0, std::ios::beg);
  vector<char> inputBuffer(bufSize);
  inputFile
      .read(inputBuffer.data(), bufSize) // read input file contents

  stream.open("output.html");
  stream << headerTag;
  stream.write(inputBuffer.data(), bufSize);
  stream << footerTag;

  stream.close();
}

} // end of namespace FactoringCommonText
