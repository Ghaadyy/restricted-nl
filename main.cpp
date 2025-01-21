#include "src/scanner.h"
#include "src/parser.h"
#include "src/ast/SeleniumASTVisitor.h"
#include "src/ast/JsonASTVisitor.h"
#include <fstream>
#include <CLI/CLI.hpp>

using namespace std;

int main(int argc, char** argv) {
    CLI::App app{"Restricted Natural Language Compiler"};

    argv = app.ensure_utf8(argv);

    std::string in_path;
    std::string out_path;
    std::string out_target;
    bool keep_xpath;

    app.add_option("-i,--input", in_path, "Input file path")->required();
    app.add_option("-o,--output", out_path, "Output file path")->required();
    app.add_option("-t,--target", out_target, "Output target (json, selenium)")
        ->check(CLI::IsMember({"json", "selenium"}))->default_val("selenium");
    app.add_flag("--keep-xpath", keep_xpath, "Keep XPATH instead of natural description (use this for testing purposes only)")->default_val(false);

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError& e) {
        return app.exit(e);
    }

    ifstream infile = ifstream(in_path);
    ofstream outfile = ofstream(out_path);

    string line;
    string file;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            file += line + "\n";
        }
        infile.close();
    }
    else {
        cerr << "Unable to open file!" << endl;
        return -1;
    }

    parser p(std::move(file));
    auto res =  p.parse();
    if(res.has_value()) {
        const auto& tree = res.value();
        ASTVisitor* visitor;

        if(out_target == "json") {
            visitor = new JsonASTVisitor();
        } else if(out_target == "selenium") {
            visitor = new SeleniumASTVisitor(keep_xpath);
        } else {
            cerr << "Invalid output target specified" << endl;
            return -1;
        }

        string code = tree.accept(*visitor);
        outfile << code;
        cout << "Compiled Successfully" << endl;
    } else {
        for(const auto& err : res.error()) {
            cout << err << endl;
        }
        cerr << "Compilation failed";
    }

    return 0;
}