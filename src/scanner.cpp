#include "scanner.h"

string yysval;

Scanner::Scanner(string&& code) :
    yyinput { code }, position { 0 }, token { 0ll } {

    if(code.empty()) return;

    rules = vector<lex_rule>({
        {"click", [&](const string & s) { return CLICK;}},
        {"visit", [&](const string & s) { return VISIT;}},
        {"button", [&](const string & s) { return BUTTON;}},
        {"link", [&](const string & s) { return LINK;}},
        {"text", [&](const string & s) { return TEXT;}},
        {"input", [&](const string & s) { return INPUT;}},
        {"image", [&](const string & s) { return IMAGE;}},
        {"is displayed", [&](const string & s) { return DISPLAYED;}},
        {"is hidden", [&](const string & s) { return HIDDEN;}},
        {"check if", [&](const string & s) { return CHECK_IF;}},
        {"with description", [&](const string & s) { return WITH_DESC;}},
        {"hover over", [&](const string & s) { return HOVER_OVER;}},
        {"on", [&](const string & s) { return ON;}},
        {"type", [&](const string & s) { return TYPE;}},
        {"[{]", [&](const string & s) { return LEFT_BRACE;}},
        {"[}]", [&](const string & s) { return RIGHT_BRACE;}},
        {"[\"]https://[a-zA-Z0-9./]*[\"]", [&](const string & s) { yysval = s; return URL;}},
        {"[a-zA-Z][a-zA-Z0-9]*", [&](const string & s) { yysval = s; return TEST_NAME;}},
        {"[\"][a-zA-Z0-9 /@='\\]\\[]*[\"]", [&](const string & s) { yysval = s; return NLD;}},
        {"[[:space:]]+",[&](const string&) { return -1; }}, // (\s, \t et \n)
        {".", [&](const string& s) { error("Unknown character", "Lexical"); return (int)s[0]; }}
    });
}

int Scanner::yylex() {
    smatch m;
    while (true) {
        if (yyinput.length() == position) return 0;
        for (auto& rule : rules)
        {
            if (regex_search(yyinput.cbegin() + position, yyinput.cend(), m,
                             regex(rule.regex), regex_constants::match_continuous)) {
                yytext = m.str();
                position += m.length();
                token = rule.lambda(yytext);
                if (token != -1) return token; else break;
            }
        }
    }
}

void Scanner::error(const string& error = "Unknown character", const string& type = "Lexical") {
    cout << type << " error : " << error << endl;
}
