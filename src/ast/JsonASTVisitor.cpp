//
// Created by A-Karam on 1/21/2025.
//

#include "JsonASTVisitor.h"
#include <nlohmann/json.hpp>
#include <sstream>

using json = nlohmann::json;

string JsonASTVisitor::visit(const VisitNode &node) {
    json json_visit = {
            {"type", "VisitNode"},
            {"url", node.get_url()}
    };

    return json_visit.dump();
}

string JsonASTVisitor::visit(const ClickNode &node) {
    json json_click = {
            {"type", "ClickNode"},
            {"description", node.get_description()},
            {"element_type", node.get_element_type()}
    };

    return json_click.dump();
}

string JsonASTVisitor::visit(const TypeNode &node) {

    json json_type = {
            {"type", "TypeNode"},
            {"description", node.get_description()},
            {"content", node.get_content()},
            {"element_type", node.get_element_type()}
    };

    return json_type.dump();
}

string JsonASTVisitor::visit(const CheckNode &node) {
    json json_check = {
            {"type", "CheckNode"},
            {"description", node.get_description()},
            {"element_type", node.get_element_type()},
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
            {"type", "TestNode"},
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
            {"type", "AST"},
            {"tests", json_tests}
    };

    return json_ast.dump();
}