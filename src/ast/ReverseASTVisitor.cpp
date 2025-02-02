//
// Created by A-Karam on 2/2/2025.
//

#include "ReverseASTVisitor.h"
#include <sstream>

string ReverseASTVisitor::visit(const VisitNode &node) {
    stringstream ss;
    ss << "visit \"" << node.get_url() << "\"";
    return ss.str();
}

string ReverseASTVisitor::visit(const ClickNode &node) {
    stringstream ss;
    ss << "click " << node.get_element_type()
       << " with description " << "\"" << node.get_description() << "\"";
    return ss.str();
}

string ReverseASTVisitor::visit(const TypeNode &node) {
    stringstream ss;
    ss << "type \"" << node.get_content() << "\" on " << node.get_element_type()
       << " with description " << "\"" << node.get_description() << "\"";
    return ss.str();
}

string ReverseASTVisitor::visit(const CheckNode &node) {
    stringstream ss;
    ss << "check if " << node.get_element_type()
       << " with description " << "\"" << node.get_description() << "\""
       << " is " << (node.get_state() ? "displayed" : "hidden");
    return ss.str();
}

string ReverseASTVisitor::visit(const TestNode &node) {
    stringstream ss;

    ss << node.testName << " {";
    for(auto& action: node.actions){
        ss << "\n\t" << action->accept(*this);
    }
    ss << "\n}";

    return ss.str();
}

string ReverseASTVisitor::visit(const AST &tree) {
    stringstream  ss;

    for(auto& test: tree.tests){
        ss << test.accept(*this) << "\n\n";
    }

    return ss.str();
}
