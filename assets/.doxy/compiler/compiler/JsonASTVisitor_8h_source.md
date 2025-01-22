

# File JsonASTVisitor.h

[**File List**](files.md) **>** [**ast**](dir_203e5988f1ed315d29383d699972de6f.md) **>** [**JsonASTVisitor.h**](JsonASTVisitor_8h.md)

[Go to the documentation of this file](JsonASTVisitor_8h.md)


```C++
//
// Created by A-Karam on 1/21/2025.
//

#ifndef RESTRICTED_NL_JSONASTVISITOR_H
#define RESTRICTED_NL_JSONASTVISITOR_H

#include "AST.h"

class JsonASTVisitor : public ASTVisitor {
public:
    string visit(const VisitNode& node) override;
    string visit(const ClickNode& node) override;
    string visit(const TypeNode& node) override;
    string visit(const CheckNode& node) override;
    string visit(const TestNode& node) override;
    string visit(const AST& tree) override;
};

#endif //RESTRICTED_NL_JSONASTVISITOR_H
```


