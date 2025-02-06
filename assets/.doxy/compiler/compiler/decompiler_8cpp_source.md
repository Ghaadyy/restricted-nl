

# File decompiler.cpp

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**decompiler.cpp**](decompiler_8cpp.md)

[Go to the documentation of this file](decompiler_8cpp.md)


```C++
//
// Created by A-Karam on 2/2/2025.
//

#include "decompiler.h"

decompiler::decompiler(string &&ast) : ast(ast) {}

expected<AST, vector<string>> decompiler::convert() {
    try {
        json parsedAST = json::parse(ast);
        vector<TestNode> tests;

        for (const auto &test : parsedAST.at("tests")) {
            auto testNode = parseTestNode(test);
            if (testNode) {
                tests.push_back(std::move(*testNode));
            }
        }

        if(!errors.empty()) return unexpected(errors);

        return AST(std::move(tests));
    } catch (const json::exception &e) {
        errors.push_back("Error: " + string(e.what()));
        return unexpected(errors);
    }
}

ActionNode* decompiler::parseActionNode(const json &action) {
    try{
        string type = action.at("action");

        if (type == "visit") {
            return new VisitNode(action.at("url"));
        } else if (type == "click") {
            return new ClickNode(action.at("elementType"), action.at("description"));
        } else if (type == "type") {
            return new TypeNode(action.at("content"), action.at("elementType"), action.at("description"));
        } else if (type == "check") {
            return new CheckNode(action.at("elementType"), action.at("description"), action.at("state"));
        } else{
            errors.emplace_back("Error: [type.exception.invalid.403] action type \'" + type + "\'" + " not found");
        }

        return nullptr;
    }catch (const json::exception &e){
        errors.push_back("Error: " + string(e.what()));
        return nullptr;
    }
}

TestNode* decompiler::parseTestNode(const json &test) {
    try{
        string testName = test.at("testName");
        vector<ActionNode*> actions;

        for (const auto &action : test.at("actions")) {
            auto actionNode = parseActionNode(action);
            if (actionNode) {
                actions.push_back(actionNode);
            }
        }

        return errors.empty() ? new TestNode(std::move(testName), actions) : nullptr;
    }catch (const json::exception &e){
        errors.push_back("Error: " + string(e.what()));
        return nullptr;
    }
}
```


