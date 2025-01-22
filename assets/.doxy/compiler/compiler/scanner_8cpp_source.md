

# File scanner.cpp

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**scanner.cpp**](scanner_8cpp.md)

[Go to the documentation of this file](scanner_8cpp.md)


```C++
#include "scanner.h"

string yysval;

Scanner::Scanner(string&& content) :
    yyinput { content }, position { 0 }, token { 0ll } {

    if(content.empty()) return;

    rules = vector<lex_rule>({
        {"click", [&](const string & s) { return CLICK;}},
        {"visit", [&](const string & s) { return VISIT;}},
        {"button", [&](const string & s) { yysval = s; return BUTTON;}},
        {"link", [&](const string & s) { yysval = s; return LINK;}},
        {"text", [&](const string & s) { yysval = s; return TEXT;}},
        {"input", [&](const string & s) { yysval = s; return INPUT;}},
        {"image", [&](const string & s) { yysval = s; return IMAGE;}},
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
        {R"(["][a-zA-Z0-9 /@='\]\[]*["])", [&](const string & s) { yysval = s; return NLD;}},
        {"[[:space:]]+", [&](const string& match) {
            for (char c : match) {
                if (c == '\n') {
                    ++line_count;
                }
            }
            return -1;
        }}, // (\s, \t et \n)
        {".", [&](const string& s) { return (int)s[0]; }}
    });
}

string Scanner::getTokenName(int tokenId) {
    static const std::unordered_map<int, std::string> tokenNames = {
            {257, "TEST_NAME"}, {258, "CLICK"}, {259, "VISIT"}, {260, "BUTTON"},
            {261, "LINK"}, {262, "TEXT"}, {263, "IMAGE"}, {264, "DISPLAYED"},
            {265, "HIDDEN"}, {266, "CHECK_IF"}, {267, "WITH_DESC"}, {268, "HOVER_OVER"},
            {269, "NLD"}, {270, "URL"}, {271, "ON"}, {272, "TYPE"},
            {273, "CONTENT"}, {274, "LEFT_BRACE"}, {275, "RIGHT_BRACE"}, {276, "INPUT"}
    };

    auto it = tokenNames.find(tokenId);
    return it != tokenNames.end() ? it->second : "UNKNOWN";
}

int Scanner::line_number() const {
    return line_count;
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
```


