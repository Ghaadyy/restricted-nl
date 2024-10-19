#ifndef RESTRICTED_NL_SELENIUM_H
#define RESTRICTED_NL_SELENIUM_H

#include "codegen.h"

class SeleniumCodeGen : public CodeGen {
private:
    unsigned long long id; // WE SHOULD CHANGE THIS!!!
public:
    void init() override;

    void createTest(const string& testName) override;
    
    void finishTest() override;

    void visit(const string& url) override;

    void click(const string& xpath) override;

    void hover(const string& xpath) override;

    void check(const string& xpath, const bool expectedValue) override;

    void type(const string& xpath, const string& text) override;

    string generate() override;
};

#endif //RESTRICTED_NL_SELENIUM_H