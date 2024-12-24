#ifndef RESTRICTED_NL_AST_H
#define RESTRICTED_NL_AST_H

#include <utility>
#include<vector>
#include<string>
#include<sstream>

using namespace std;

class ASTVisitor;

class ActionNode {
public:
    ActionNode() = default;
    virtual string accept(ASTVisitor& visitor) const = 0;
};

class VisitNode : public ActionNode {
private:
    string url;
public:
    explicit VisitNode(string&& url);
    string accept(ASTVisitor& visitor) const override;
    string get_url() const {
        return url;
    }
};

class ClickNode : public ActionNode {
private:
    string element_type;
    string description;
public:
    explicit ClickNode(string&& element_type, string&& description);
    string accept(ASTVisitor& visitor) const override;
    string get_element_type() const;
    string get_description() const;
};

class TypeNode : public ActionNode {
    string content;
    string element_type;
    string description;
public:
    explicit TypeNode(string&& content, string&& element_type, string&& description);
    string accept(ASTVisitor& visitor) const override;
    string get_content() const;
    string get_element_type() const;
    string get_description() const;
};

class CheckNode : public ActionNode {
private:
    string element_type;
    string description;
    bool state;
public:
    explicit CheckNode(string&& element_type, string&& description, bool state);
    string accept(ASTVisitor& visitor) const override;
    string get_element_type() const;
    string get_description() const;
    bool get_state() const;
};

class TestNode {
public:
    string testName;
    vector<ActionNode*> actions;
    string accept(ASTVisitor& visitor) const;
};

class AST {
public:
    vector<TestNode> tests;
    string accept(ASTVisitor& visitor) const;
};

class ASTVisitor {
public:
    virtual string visit(const VisitNode& node)  = 0;
    virtual string visit(const ClickNode& node)  = 0;
    virtual string visit(const TypeNode& node)  = 0;
    virtual string visit(const CheckNode& node)  = 0;
    virtual string visit(const TestNode& node)  = 0;
    virtual string visit(const AST& tree)  = 0;
};

#endif //RESTRICTED_NL_AST_H