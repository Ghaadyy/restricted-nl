#include "src/scanner.h"
#include "src/parser.h"
#include "src/codegen/selenium.h"
#include <fstream>

using namespace std;

int main() {
  ifstream infile = ifstream("tests.txt");
  string line;
  string file;
  if (infile.is_open()) {
      while (getline(infile, line)) {
          file += line + "\n";
      }
      infile.close();
  }
  else {
      cerr << "Unable to open file!" << endl;
      return false;
  }

  parser p(std::move(file), new SeleniumCodeGen());

  if (p.parse()) {
    cout << "Compiled successfully" << endl;
  } else {
    cout << "Failed to compile" << endl;
  }

  return 0;
}