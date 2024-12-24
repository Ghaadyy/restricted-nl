#include "src/scanner.h"
#include "src/parser.h"
#include "src/ast/SeleniumASTVisitor.h"
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

  parser p(std::move(file));
  auto res =  p.parse();
  if(res.has_value()) {
      const auto& tree = res.value();
      SeleniumASTVisitor visitor;
      string code = tree.accept(visitor);
      outfile << code;
      cout << "Compiled Successfully" << endl;
  } else{
      for(const auto& err : res.error()) {
          cout << err << endl;
      }
      cerr << "Compilation failed";
  }

  return 0;
}