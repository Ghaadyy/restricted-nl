#include "src/scanner.h"
#include "src/parser.h"
#include "src/codegen/selenium.h"
#include <fstream>

#define NUM_ARGS  (3)

using namespace std;

int main(int argc, const char** argv) {
  if(argc != NUM_ARGS) {
    cerr  << "You must provide two arguments."        << endl
          << "  e.g. ./restricted-nl in.txt out.txt"  << endl;
    return -1;
  }

  string in_path = argv[1];
  string out_path = argv[2];

  ifstream infile = ifstream(in_path);
  ofstream outfile = ofstream(out_path);

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
      return -1;
  }

  parser p(std::move(file), new SeleniumCodeGen());

  const char* code;

  if (!p.parse(&code)) {
    cerr << "Failed to compile" << endl;
    return -1;
  }

  cout << "Compiled Successfully" << endl;

  outfile << code;

  return 0;
}