#include "Scanner.h"

bool Scanner::read_file(const string &path) {
    // isOpen = false;
    // ifstream infile = ifstream(path);
    // string line;
    // yyinput = "";
    // if (infile.is_open()) {
    //     while (getline(infile, line)) {
    //         yyinput += line + "\n";
    //     }
    //     infile.close();
    //     isOpen = true;
    // }
    // else {
    //     cerr << "Unable to open file!" << endl;
    //     return false;
    // }

    // TODO: ability to either read from file or take from stdin
    isOpen = true;
    yyinput = path;
    return true;
}

Scanner::Scanner(string &&file_name) :
    file_name { file_name }, isOpen { false }, position { 0 }, token { 0ll } {

    if(!read_file(file_name)) return;

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
        {"url", [&](const string & s) { return URL;}},
        {"on", [&](const string & s) { return ON;}},
        {"type", [&](const string & s) { return TYPE;}},
        {"[{]", [&](const string & s) { return LEFT_BRACE;}},
        {"[}]", [&](const string & s) { return RIGHT_BRACE;}},
        {"[a-zA-Z][a-zA-Z0-9]*", [&](const string & s) { return TEST_NAME;}},
        {"[\"][a-zA-Z0-9 ]*[\"]", [&](const string & s) { return NLD;}},
        {"[[:space:]]+",[&](const string&) { return -1; }}, // (\s, \t et \n)
        {".", [&](const string& s) { error("Unknown character", "Lexical"); return (int)s[0]; }}
    });
}

int Scanner::yylex() {
    if (!isOpen) return 0;
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
