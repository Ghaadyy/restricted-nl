#ifndef RESTRICTED_NL_CODEGEN_H
#define RESTRICTED_NL_CODEGEN_H

#include <sstream>
#include <string>

using namespace std;

class CodeGen {
public:
    stringstream ss;
    virtual void init() = 0;
    virtual void createTest(const string&) = 0;
    virtual void finishTest() = 0;
    virtual void visit(const string&) = 0; 
    virtual void click(const string&) = 0; 
    virtual void hover(const string&) = 0; 
    virtual void check(const string&, const bool) = 0;
    virtual void type(const string&, const string&) = 0;
    virtual string generate() = 0;
};

#endif //RESTRICTED_NL_CODEGEN_H