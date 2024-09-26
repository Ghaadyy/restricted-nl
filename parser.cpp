#include "parser.h"

//-- Program Structure
//program -> test program | epsilon
//test -> TEST_NAME { body }
//body -> action body | epsilon
//action -> click | hover | check | type | visit
//elem_type -> BUTTON | LINK | TEXT | IMAGE | INPUT
//
//-- Actions
//visit -> VISIT URL
//click -> CLICK elem_type WITH_DESC NLD ?and value?
//hover -> HOVER_OVER elem_type WITH_DESC NLD
//check -> CHECK_IF elem_type WITH_DESC NLD state
//type -> TYPE CONTENT ON elem_type WITH_DESC NLD
//
//-- State
//state -> DISPLAYED | HIDDEN

parser::parser(string&& path) : scanner { Scanner(std::move(path)) } {}

bool parser::program() { //program -> test program | epsilon
    if(token == 0) return true; // program -> epsilon
    if(!test()) return false;
    if(!program()) return false;

    return true; // program -> test program
}

bool parser::test() {
    if(token == TEST_NAME) {
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

            token = scanner.yylex();
            if(!state()) return false;
        } else {
            return false;
        }

        token = scanner.yylex();
        return true;
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
    token = scanner.yylex();
    if(token != ON) return false;
    token = scanner.yylex();
    if(!elem_type()) return false;
    if(token != WITH_DESC) return false;
    token = scanner.yylex();
    if(token != NLD) return false;
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

bool parser::parse() {
    token = scanner.yylex();
    if (program()) {
        return true;
    }

    cerr << "Syntax error\n";
    return false;
}
