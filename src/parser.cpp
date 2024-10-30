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

bool parser::test() {
    if(token == TEST_NAME) {
        codeGen->createTest(yysval);
        token = scanner.yylex();
        if(token == LEFT_BRACE) {
            token = scanner.yylex();
            if(!body()) return false;

            if(token != RIGHT_BRACE) {
                return false;
            }
        }else{
            return false;
        }

        codeGen->finishTest();
        token = scanner.yylex();
        return true;
    }

    return false;
}

bool parser::action() {
    if(click()) return true;
    if(hover()) return true;
    if(visit()) return true;
    if(type()) return true;
    if(check()) return true;

    return false;
}

bool parser::visit() {
    if(token == VISIT) {
        token = scanner.yylex();

        if(token != URL) {
            return false;
        }

        codeGen->visit(yysval);
        
        token = scanner.yylex();
        return true;
    }

    return false;
}

bool parser::body() {
    if(action()) {
        if(!body()) return false;
        return true;
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
        if(!elem_type()) return false;
        if(token == WITH_DESC) {
            token = scanner.yylex();

            if(token != NLD) return false;
        }else{
            return false;
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
        if(!elem_type()) return false;
        if(token == WITH_DESC) {
            token = scanner.yylex();
            if(token != NLD) return false;
            
            string xpath = yysval;
            token = scanner.yylex();
            codeGen->check(xpath, token == DISPLAYED);
            return state();
        }
    }

    return false;
}

bool parser::hover() {
    if(token == HOVER_OVER) {
        token = scanner.yylex();
        if(!elem_type()) return false;
        if(token == WITH_DESC) {
            token = scanner.yylex();

            if(token != NLD) return false;
        } else {
            return false;
        }

        token = scanner.yylex();
        return true;
    }

    return false;
}

bool parser::type() {
    if(token != TYPE) return false;
    token = scanner.yylex();
    if(token != NLD) return false; // TODO: IT SHOULD BE CONTENT
    string content = yysval;
    token = scanner.yylex();
    if(token != ON) return false;
    token = scanner.yylex();
    if(!elem_type()) return false;
    if(token != WITH_DESC) return false;
    token = scanner.yylex();
    if(token != NLD) return false;

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

bool parser::parse(const char** code) {
    codeGen->init();
    token = scanner.yylex();
    if (program()) {
        string output = codeGen->generate();
        *code = strdup(output.c_str());
        return true;
    }
    
    return false;
}
