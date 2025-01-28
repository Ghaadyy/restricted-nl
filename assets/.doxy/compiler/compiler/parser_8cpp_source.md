

# File parser.cpp

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**parser.cpp**](parser_8cpp.md)

[Go to the documentation of this file](parser_8cpp.md)


```C++
#include "parser.h"
#include "ast/SeleniumASTVisitor.h"

parser::parser(string&& content)
    : scanner { Scanner(std::move(content)) }, tree(AST()) {}

bool parser::program() { //program -> test program | epsilon
    if(token == 0) return true; // program -> epsilon
    if(!test()) return false;
    if(!program()) return false;

    return true; // program -> test program
}

bool parser::test() {
    if(token == TEST_NAME) {
        tree.tests.emplace_back(std::move(yysval), vector<ActionNode*>());
        token = scanner.yylex();
        if(token == LEFT_BRACE) {
            token = scanner.yylex();
            if(!body()){
                return recoverFromError({TEST_NAME});
            }

            if(token != RIGHT_BRACE) {
                reportError("RIGHT BRACE");
                return recoverFromError({TEST_NAME});
            }
        }else{
            reportError("LEFT BRACE");
            return recoverFromError({TEST_NAME});
        }

        token = scanner.yylex();
        return true;
    }

    reportError("TEST NAME");
    return recoverFromError({TEST_NAME});
}

bool parser::action() {
    switch (token) {
        case CLICK:
            return click();
        case HOVER_OVER:
            return hover();
        case VISIT:
            return visit();
        case TYPE:
            return type();
        case CHECK_IF:
            return check();
        default:
            return false;
    }
}


bool parser::visit() {
    if(token == VISIT) {
        token = scanner.yylex();

        if(token != URL) {
            reportError("URL");
            return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
        }

        tree.tests.back().actions.push_back(new VisitNode(std::move(yysval)));

        token = scanner.yylex();
        return true;
    }

    return false;
}

bool parser::body() {
    if(token == CLICK || token == HOVER_OVER || token == TYPE || token == CHECK_IF || token == VISIT) {
        return action() && body();
    }

    return true;
}

bool parser::elem_type() {
    if(token == BUTTON || token == LINK || token == TEXT || token == IMAGE || token == INPUT){
        token = scanner.yylex();
        return true;
    }

    return false;
}

bool parser::click() {
    vector<Tokens> recoveryTokens = {CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE};
    if(token == CLICK) {
        token = scanner.yylex();
        string element_type = yysval;
        if(!elem_type()){
            reportError("ELEMENT TYPE");
            return recoverFromError(recoveryTokens);
        }
        if(token == WITH_DESC) {
            token = scanner.yylex();

            if(token != NLD) {
                reportError("NLD");
                return recoverFromError(recoveryTokens);
            }
        }else{
            reportError("WITH DESCRIPTION");
            return recoverFromError(recoveryTokens);
        }

        tree.tests.back().actions.push_back(new ClickNode(std::move(element_type), std::move(yysval)));

        token = scanner.yylex();
        return true;
    }

    return false;
}

bool parser::check() {
    vector<Tokens> recoveryTokens = {CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE};
    if(token == CHECK_IF) {
        token = scanner.yylex();
        string element_type = yysval;
        if(!elem_type()){
            reportError("ELEMENT TYPE");
            return recoverFromError(recoveryTokens);
        }
        if(token == WITH_DESC) {
            token = scanner.yylex();
            if(token != NLD){
                reportError("NLD");
                return recoverFromError(recoveryTokens);
            }
            
            string xpath = yysval;
            token = scanner.yylex();
            tree.tests.back().actions.push_back(new CheckNode(std::move(element_type), std::move(xpath), token == DISPLAYED));
            if(state()){
                return true;
            }else{
                reportError("STATE");
                return recoverFromError(recoveryTokens);
            }
        }else{
            reportError("WITH DESCRIPTION");
            return recoverFromError(recoveryTokens);
        }
    }

    return false;
}

bool parser::hover() {
    vector<Tokens> recoveryTokens = {CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE};
    if(token == HOVER_OVER) {
        token = scanner.yylex();
        if(!elem_type()){
            reportError("ELEMENT TYPE");
            return recoverFromError(recoveryTokens);
        }
        if(token == WITH_DESC) {
            token = scanner.yylex();

            if(token != NLD){
                reportError("NLD");
                return recoverFromError(recoveryTokens);
            }
        } else {
            reportError("WITH DESCRIPTION");
            return recoverFromError(recoveryTokens);
        }

        token = scanner.yylex();
        return true;
    }

    return false;
}

bool parser::type() {
    vector<Tokens> recoveryTokens = {CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE};
    if(token != TYPE) return false;
    token = scanner.yylex();
    if(token != NLD) {
        reportError("CONTENT");
        return recoverFromError(recoveryTokens);
    } // TODO: IT SHOULD BE CONTENT
    string content = yysval;
    token = scanner.yylex();
    if(token != ON){
        reportError("ON");
        return recoverFromError(recoveryTokens);
    }
    token = scanner.yylex();
    string element_type = yysval;
    if(!elem_type()){
        reportError("ELEMENT TYPE");
        return recoverFromError(recoveryTokens);
    }
    if(token != WITH_DESC){
        reportError("WITH DESCRIPTION");
        return recoverFromError(recoveryTokens);
    }
    token = scanner.yylex();
    if(token != NLD){
        reportError("NLD");
        return recoverFromError(recoveryTokens);
    }


    tree.tests.back().actions.push_back(new TypeNode(std::move(content), std::move(element_type), std::move(yysval)));

    token = scanner.yylex();
    return true;
}

bool parser::state() {
    if(token == DISPLAYED || token == HIDDEN) {
        token = scanner.yylex();
        return true;
    }

    return false;
}

bool parser::recoverFromError(const vector<enum Tokens>& syncSet) {
    while (token != 0) {
        for (auto syncToken : syncSet) {
            if (token == syncToken) {
                cerr << "[Recovery] Found synchronizing token: " << Scanner::getTokenName(token) << " at line " <<
                        to_string(scanner.line_number()) << endl;
                return true;
            }
        }
        token = scanner.yylex();
    }

    cerr << "Failed to recover. Reached EOF.\n";
    return false;
}

void parser::reportError(const string& expectedToken) {
    errors.push_back("Expected " + expectedToken + ", but found " + Scanner::getTokenName(token) + " instead at line " + std::to_string(scanner.line_number()));
}

expected<AST, vector<string>> parser::parse() {
    token = scanner.yylex();
    if (program() && errors.empty()) {
        return tree;
    }

    return unexpected(errors);
}
```


