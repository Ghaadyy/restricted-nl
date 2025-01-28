//
// Created by Ghady Youssef on 24/12/2024.
//

#include "AST.h"

ClickNode::ClickNode(string &&element_type, string &&description) : element_type(std::move(element_type)), description(std::move(description)), ActionNode() {}

TypeNode::TypeNode(string &&content, string &&element_type, string &&description) : content(std::move(content)), element_type(std::move(element_type)), description(std::move(description)) {}

VisitNode::VisitNode(string &&url) : url(std::move(url)), ActionNode() {}

CheckNode::CheckNode(string &&element_type, string &&description, bool state) : element_type(std::move(element_type)), description(std::move(description)), state(state), ActionNode() {}

TestNode::TestNode(string&& testName, vector<ActionNode *> actions) : testName(std::move(testName)), actions(std::move(actions)) {}

AST::AST() : tests(vector<TestNode>()) {}

AST::AST(vector<TestNode> tests) : tests(std::move(tests)) {}

string ClickNode::accept(ASTVisitor &visitor) const {
    return visitor.visit(*this);
}

string TypeNode::accept(ASTVisitor &visitor) const {
    return visitor.visit(*this);
}

string CheckNode::accept(ASTVisitor &visitor) const {
    return visitor.visit(*this);
}

string VisitNode::accept(ASTVisitor &visitor) const {
    return visitor.visit(*this);
}

string AST::accept(ASTVisitor &visitor) const {
    return visitor.visit(*this);
}

string TestNode::accept(ASTVisitor &visitor) const {
    return visitor.visit(*this);
}

string TypeNode::get_element_type() const {
    return element_type;
}

string TypeNode::get_description() const {
    return description;
}

string TypeNode::get_content() const {
    return content;
}

string CheckNode::get_element_type() const {
    return element_type;
}

string CheckNode::get_description() const {
    return description;
}

bool CheckNode::get_state() const {
    return state;
}

string ClickNode::get_element_type() const {
    return element_type;
}

string ClickNode::get_description() const {
    return description;
}