//
// Created by Ghady Youssef on 16/09/2024.
//

#ifndef RESTRICTED_NL_PARSER_H
#define RESTRICTED_NL_PARSER_H

#include <string>
#include "scanner.h"
#include "codegen/codegen.h"
#include "codegen/selenium.h"

using namespace std;

class parser {
private:
    CodeGen* codeGen;
public:
    Scanner scanner;
    int token {};
    long long number {};

    parser(string&&, CodeGen*);

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

    bool parse();
};

#ifdef _WIN32
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __attribute__((visibility("default")))
#endif

extern "C" inline DLL_API bool parse(const char *path) {
    parser p(path, new SeleniumCodeGen());
    return p.parse();
}

#endif //RESTRICTED_NL_PARSER_H
