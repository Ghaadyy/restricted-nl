

# File JsonASTVisitor.cpp

[**File List**](files.md) **>** [**ast**](dir_203e5988f1ed315d29383d699972de6f.md) **>** [**JsonASTVisitor.cpp**](JsonASTVisitor_8cpp.md)

[Go to the documentation of this file](JsonASTVisitor_8cpp.md)


```C++
//
// Created by A-Karam on 1/21/2025.
//

#include "JsonASTVisitor.h"
#include <nlohmann/json.hpp>
#include <sstream>

using json = nlohmann::json;

string JsonASTVisitor::visit(const VisitNode &node) {
    json json_visit = {
            {"action", "visit"},
            {"url", node.get_url()}
    };

    return json_visit.dump();
}

string JsonASTVisitor::visit(const ClickNode &node) {
    json json_click = {
            {"action", "click"},
            {"description", node.get_description()},
            {"elementType", node.get_element_type()}
    };

    return json_click.dump();
}

string JsonASTVisitor::visit(const TypeNode &node) {

    json json_type = {
            {"action", "type"},
            {"description", node.get_description()},
            {"content", node.get_content()},
            {"elementType", node.get_element_type()}
    };

    return json_type.dump();
}

string JsonASTVisitor::visit(const CheckNode &node) {
    json json_check = {
            {"action", "check"},
            {"description", node.get_description()},
            {"elementType", node.get_element_type()},
            {"state", node.get_state()}
    };

    return json_check.dump();
}

string JsonASTVisitor::visit(const TestNode &node) {
    vector<json> json_actions;

    for(auto& action : node.actions) {
        json_actions.push_back(json::parse(action->accept(*this)));
    }

    json json_test = {
            {"testName", node.testName},
            {"actions", json_actions}
    };

    return json_test.dump();
}

string JsonASTVisitor::visit(const AST &tree) {
    vector<json> json_tests;

    for(auto& test : tree.tests) {
        json_tests.push_back(json::parse(test.accept(*this)));
    }

    json json_ast = {
            {"tests", json_tests}
    };

    return json_ast.dump();
}
```


