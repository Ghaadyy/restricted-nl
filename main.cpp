#include "Scanner.h"
#include "parser.h"

std::string tokenToString(int token) {
    switch (token) {
        case TEST_NAME: return "TEST_NAME";
        case CLICK: return "CLICK";
        case VISIT: return "VISIT";
        case BUTTON: return "BUTTON";
        case LINK: return "LINK";
        case TEXT: return "TEXT";
        case IMAGE: return "IMAGE";
        case DISPLAYED: return "DISPLAYED";
        case HIDDEN: return "HIDDEN";
        case CHECK_IF: return "CHECK_IF";
        case WITH_DESC: return "WITH_DESC";
        case HOVER_OVER: return "HOVER_OVER";
        case INPUT: return "INPUT";
        case NLD: return "NLD";
        case URL: return "URL";
        case ON: return "ON";
        case TYPE: return "TYPE";
        case LEFT_BRACE: return "LEFT_BRACE";
        case RIGHT_BRACE: return "RIGHT_BRACE";
        default: return "UNKNOWN_TOKEN";
    }
}


int main() {
    parser p("example.txt");
    cout << p.parse() << endl;

//    Scanner scanner("example.txt");
//
//    while(true) {
//        auto token = scanner.yylex();
//        cout << tokenToString(token) << ", ";
//        if(token == 0) break;
//    }

    return 0;
}

//terminate called after throwing an instance of 'std::regex_error'
//what():  Mismatched '(' and ')' in regular expression