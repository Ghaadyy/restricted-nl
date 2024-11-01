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

  string inpath = argv[1];
  string outpath = argv[2];

  ifstream infile = ifstream(inpath);
  ofstream outfile = ofstream(outpath);

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

  const char* code;

  if (!p.parse(&code)) {
    cerr << "Failed to compile" << endl;
    return -1;
  }

  outfile << code;

  return 0;
}