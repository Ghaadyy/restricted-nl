//
// Created by King Antoine on 24/12/2024.
//

#ifndef RESTRICTED_NL_SELENIUMASTVISITOR_H
#define RESTRICTED_NL_SELENIUMASTVISITOR_H

#include "AST.h"

class SeleniumASTVisitor : public ASTVisitor {
public:
    string visit(const VisitNode& node) override;
    string visit(const ClickNode& node) override;
    string visit(const TypeNode& node) override;
    string visit(const CheckNode& node) override;
    string visit(const TestNode& node) override;
    string visit(const AST& tree) override;
};

#endif //RESTRICTED_NL_SELENIUMASTVISITOR_H
