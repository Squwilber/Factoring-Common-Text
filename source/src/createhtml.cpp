#include <createhtml.h>
#include <fsstream>
#include <iostream>
using namespace std;

namespace FactoringCommonText {

void createHTMLForGivenText() {

  ofstream inputFile;
  inputFile.open("output.html");
  inputFile << "Insert starting tag of HTML";
  inputFile << "Insert Contenets from input text file";

  inputFile << "Insert snd tag of HTML";
  inputFile.close();
}

} // end of namespace FactoringCommonText
