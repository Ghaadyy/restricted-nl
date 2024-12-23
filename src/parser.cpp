#include "parser.h"
#include <string.h>

parser::parser(string&& path, CodeGen* codeGen) 
    : scanner { Scanner(std::move(path)) }, codeGen(codeGen) {}

bool parser::program() { //program -> test program | epsilon
    if(token == 0) return true; // program -> epsilon
    if(!test()) return false;
    if(!program()) return false;

    return true; // program -> test program
}

//If fault in test function, RECOVER BY SKIPPING TO THE NEXT TEST
bool parser::test() {
    if(token == TEST_NAME) {
        codeGen->createTest(yysval);
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

        codeGen->finishTest();
        token = scanner.yylex();
        return true;
    }

    reportError("TEST NAME");
    return recoverFromError({TEST_NAME});
}

//If fault in action function, RECOVER BY SKIPPING TO THE NEXT ACTION OR END OF TEST (RIGHT BRACE)
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

        codeGen->visit(yysval);

        token = scanner.yylex();
        return true;
    }

    return false;
}

bool parser::body() {
    if(token == CLICK || token == HOVER_OVER || token == TYPE || token == CHECK_IF || token == VISIT){
        if(action()) {
            return body();
        }else{
            return false;
        }
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

        codeGen->click(yysval);

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
        if(token == WITH_DESC) {
            token = scanner.yylex();
            if(token != NLD){
                reportError("NLD");
                return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
            }
            
            string xpath = yysval;
            token = scanner.yylex();
            codeGen->check(xpath, token == DISPLAYED);
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
    if(token != WITH_DESC){
        reportError("WITH DESCRIPTION");
        return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
    }
    token = scanner.yylex();
    if(token != NLD){
        reportError("NLD");
        return recoverFromError({CLICK, HOVER_OVER, VISIT, TYPE, CHECK_IF, RIGHT_BRACE});
    }

    codeGen->type(yysval, content);

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
                errors.push_back("[Recovery] Found synchronizing token: " + scanner.getTokenName(token) + " at line " +
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
    errors.push_back("[Error] Expected " + expectedToken + ", but found " + scanner.getTokenName(token) + " instead at line " + std::to_string(scanner.line_number()) + "\n");
}

bool parser::parse(const char** code) {
    codeGen->init();
    token = scanner.yylex();
    if (program() && errors.empty()) {
        string output = codeGen->generate();
        *code = strdup(output.c_str());
        return true;
    }

    for(const auto & error : errors){
        cout << error;
    }

    return false;
}

#ifdef _WIN32
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __attribute__((visibility("default")))
#endif
extern "C" DLL_API bool parse(const char *path, const char** code) {
    parser p(path, new SeleniumCodeGen());
    return p.parse(code);
}