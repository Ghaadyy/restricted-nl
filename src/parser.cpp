#include "parser.h"
#include <cstring>
#include "ast/SeleniumASTVisitor.h"

parser::parser(string&& content)
    : scanner { Scanner(std::move(content)) } {}

bool parser::program() { //program -> test program | epsilon
    if(token == 0) return true; // program -> epsilon
    if(!test()) return false;
    if(!program()) return false;

    return true; // program -> test program
}

bool parser::test() {
    if(token == TEST_NAME) {
        tree.tests.push_back(TestNode(yysval, vector<ActionNode*>()));
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
    if(token == CLICK) {
        token = scanner.yylex();
        if(!elem_type()){
            reportError("ELEMENT TYPE");
            return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
        }
        string element_type = yysval;
        if(token == WITH_DESC) {
            token = scanner.yylex();

            if(token != NLD) {
                reportError("NLD");
                return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
            }
        }else{
            reportError("WITH DESCRIPTION");
            return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
        }

        tree.tests.back().actions.push_back(new ClickNode(std::move(element_type), std::move(yysval)));

        token = scanner.yylex();
        return true;
    }

    return false;
}

bool parser::check() {
    if(token == CHECK_IF) {
        token = scanner.yylex();
        if(!elem_type()){
            reportError("ELEMENT TYPE");
            return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
        }
        string element_type = yysval;
        if(token == WITH_DESC) {
            token = scanner.yylex();
            if(token != NLD){
                reportError("NLD");
                return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
            }
            
            string xpath = yysval;
            token = scanner.yylex();
            tree.tests.back().actions.push_back(new CheckNode(std::move(element_type), std::move(xpath), token == DISPLAYED));
            if(state()){
                return true;
            }else{
                reportError("STATE");
                return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
            }
        }else{
            reportError("WITH DESCRIPTION");
            return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
        }
    }

    return false;
}

bool parser::hover() {
    if(token == HOVER_OVER) {
        token = scanner.yylex();
        if(!elem_type()){
            reportError("ELEMENT TYPE");
            return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
        }
        if(token == WITH_DESC) {
            token = scanner.yylex();

            if(token != NLD){
                reportError("NLD");
                return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
            }
        } else {
            reportError("WITH DESCRIPTION");
            return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
        }

        token = scanner.yylex();
        return true;
    }

    return false;
}

bool parser::type() {
    if(token != TYPE) return false;
    token = scanner.yylex();
    if(token != NLD) {
        reportError("CONTENT");
        return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
    } // TODO: IT SHOULD BE CONTENT
    string content = yysval;
    token = scanner.yylex();
    if(token != ON){
        reportError("ON");
        return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
    }
    token = scanner.yylex();
    if(!elem_type()){
        reportError("ELEMENT TYPE");
        return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
    }
    string element_type = yysval;
    if(token != WITH_DESC){
        reportError("WITH DESCRIPTION");
        return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
    }
    token = scanner.yylex();
    if(token != NLD){
        reportError("NLD");
        return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
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
                errors.push_back("[Recovery] Found synchronizing token: " + Scanner::getTokenName(token) + " at line " +
                                         to_string(scanner.line_number()) + "\n");
                return true;
            }
        }
        token = scanner.yylex();
    }

    cerr << "Failed to recover. Reached EOF.\n";
    return false;
}

void parser::reportError(const string& expectedToken) {
    errors.push_back("[Error] Expected " + expectedToken + ", but found " + Scanner::getTokenName(token) + " instead at line " + std::to_string(scanner.line_number()));
}

expected<AST, vector<string>> parser::parse() {
    token = scanner.yylex();
    if (program() && errors.empty()) {
        return tree;
    }

    return unexpected(errors);
}

#ifdef _WIN32
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __attribute__((visibility("default")))
#endif
extern "C" DLL_API bool parse(const char *path, const char** code) {
    parser p(path);
    auto res =  p.parse();
    if(res.has_value()) {
        const auto& tree = res.value();
        SeleniumASTVisitor visitor;
        string output = tree.accept(visitor);
        *code = strdup(output.c_str());
        return true;
    }
    return "Compilation failed";
}