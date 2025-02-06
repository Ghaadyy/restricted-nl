//
// Created by A-Karam on 2/2/2025.
//

#ifndef RESTRICTED_NL_SOURCEASTVISITOR_H
#define RESTRICTED_NL_SOURCEASTVISITOR_H


#include "AST.h"

class SourceASTVisitor : public ASTVisitor {
public:
    string visit(const VisitNode& node) override;
    string visit(const ClickNode& node) override;
    string visit(const TypeNode& node) override;
    string visit(const CheckNode& node) override;
    string visit(const TestNode& node) override;
    string visit(const AST& tree) override;
};


#endif //RESTRICTED_NL_SOURCEASTVISITOR_H
