

# File scanner.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**scanner.h**](scanner_8h.md)

[Go to the documentation of this file](scanner_8h.md)


```C++
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

enum Tokens {   TEST_NAME = 257, CLICK, VISIT, BUTTON, LINK, TEXT, IMAGE, DISPLAYED, HIDDEN, CHECK_IF, 
                WITH_DESC, HOVER_OVER, NLD, URL, ON, TYPE, CONTENT, LEFT_BRACE, RIGHT_BRACE, INPUT };

extern string yysval;

struct lex_rule {
    string regex;
    function<int(const string&)> lambda;
};

class Scanner {
private:
    int line_count = 1;
    string yytext;
    string yyinput;
    int token;
    long long position = 0;
    vector<lex_rule> rules;

public:
    explicit Scanner(string&& content);

    static string getTokenName(int tokenId);

    int line_number() const;

    int yylex();
};

#endif //RESTRICTED_NL_SCANNER_H
```


