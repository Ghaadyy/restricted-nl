

# File parser.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**parser.h**](parser_8h.md)

[Go to the documentation of this file](parser_8h.md)


```C++
//
// Created by Ghady Youssef on 16/09/2024.
//

#ifndef RESTRICTED_NL_PARSER_H
#define RESTRICTED_NL_PARSER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <expected>
#include "scanner.h"
#include "ast/AST.h"

using namespace std;

class parser {
private:
    vector<string> errors;
    Scanner scanner;
    int token {};
    AST tree;

    bool program();
    bool body();
    bool action();
    bool elem_type();
    bool test();
    bool visit();
    bool click();
    bool hover();
    bool check();
    bool type();
    bool state();

    bool recoverFromError(const vector<enum Tokens>&);
    void reportError(const string& expectedToken);

public:
    explicit parser(string&& content);

    expected<AST, vector<string>> parse();
};

#endif //RESTRICTED_NL_PARSER_H
```


