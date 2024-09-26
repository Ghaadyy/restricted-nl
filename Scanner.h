#ifndef RESTRICTED_NL_SCANNER_H
#define RESTRICTED_NL_SCANNER_H

#include <string>
#include <map>
#include <functional>
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

enum Tokens { TEST_NAME = 257, CLICK, VISIT, BUTTON, LINK, TEXT, IMAGE, DISPLAYED, HIDDEN, CHECK_IF, WITH_DESC, HOVER_OVER, NLD, URL, ON, TYPE, CONTENT, LEFT_BRACE, RIGHT_BRACE, INPUT };

//long long yylval = 0;   // Value of the number
//string yysval;          // Name of the identifier
//map<string, long long> vars;    // Table of variables

struct lex_rule {
    string regex;
    function<int(const string&)> lambda;
};

class Scanner {
private:
    string yytext;
    string yyinput;
    int token;
    long long position = 0;
    string file_name;
    bool isOpen = false;
    vector<lex_rule> rules;

    bool read_file(const string&);

public:
    explicit Scanner(string&& path);

    int yylex();

    static void error(const string&, const string&);
};

#endif //RESTRICTED_NL_SCANNER_H
