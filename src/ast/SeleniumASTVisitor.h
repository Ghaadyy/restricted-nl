//
// Created by King Antoine on 24/12/2024.
//

#ifndef RESTRICTED_NL_SELENIUMASTVISITOR_H
#define RESTRICTED_NL_SELENIUMASTVISITOR_H

#include "AST.h"

class SeleniumASTVisitor : public ASTVisitor {
private:
    bool keep_xpath;
    static string generate_init();
    static string generate_xpath_helper();
    static string generate_seeclick_helper();
    static string init_hooks();
    static string get_coordinates();
    static string element_from_point();
    static string end();
public:
    explicit SeleniumASTVisitor(bool keep_xpath) : keep_xpath(keep_xpath) {}
    string visit(const VisitNode& node) override;
    string visit(const ClickNode& node) override;
    string visit(const TypeNode& node) override;
    string visit(const CheckNode& node) override;
    string visit(const TestNode& node) override;
    string visit(const AST& tree) override;
};

#endif //RESTRICTED_NL_SELENIUMASTVISITOR_H
