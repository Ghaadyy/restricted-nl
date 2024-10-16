//
// Created by Ghady Youssef on 16/09/2024.
//

#ifndef RESTRICTED_NL_PARSER_H
#define RESTRICTED_NL_PARSER_H

#include <string>
#include "scanner.h"

using namespace std;

//-- Program Structure
//program -> test program | epsilon
//        test -> TEST_NAME { body }
//body -> action body | epsilon
//        action -> click | hover | check | type | visit
//        elem_type -> BUTTON | LINK | TEXT | IMAGE | INPUT
//
//-- Actions
//        visit -> VISIT URL
//click -> CLICK elem_type WITH_DESC NLD ?and value?
//hover -> HOVER_OVER elem_type WITH_DESC NLD
//check -> CHECK_IF elem_type WITH_DESC NLD state
//        type -> TYPE CONTENT ON elem_type WITH_DESC NLD
//
//-- State
//state -> DISPLAYED | HIDDEN

class parser {
public:
    Scanner scanner;
    int token {};
    long long number {};

    explicit parser(string&&);

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
    parser p(path);
    return p.parse();
}

#endif //RESTRICTED_NL_PARSER_H