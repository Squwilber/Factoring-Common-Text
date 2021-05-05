#include "../includes/createhtml.h"
using namespace std;

const string headerTag = "<html><head></head><body>";
const string footerTag = "</body></html>";

void HandleHTML::createHTMLForGivenText() {
  ofstream stream;
  ifstream inputFile("input.txt", std::ios::binary | std::ios::ate);
  streamsize bufSize = inputFile.tellg();
  inputFile.seekg(0, std::ios::beg);
  vector<char> inputBuffer(bufSize);
  inputFile.read(inputBuffer.data(), bufSize); // read input file contents

  stream.open("output.html");
  stream << headerTag;
  stream.write(inputBuffer.data(), bufSize);
  stream << footerTag;

  stream.close();
}

int main() {
  HandleHTML b;
  b.createHTMLForGivenText();
  return 0;
}
