#include "src/scanner.h"
#include "src/parser.h"
#include "src/ast/SeleniumASTVisitor.h"
#include "src/ast/JsonASTVisitor.h"
#include "src/ast/SourceASTVisitor.h"
#include "src/decompiler.h"
#include <fstream>
#include <CLI/CLI.hpp>

std::string in_path;
std::string out_path;
std::string out_target;
bool keep_xpath;

std::string read_source(std::istream& stream) {
    std::string file, line;
    while (std::getline(stream, line)) file += line + "\n";
    return file;
}

void show_errors(const std::vector<std::string>& errors) {
    for (const auto &err: errors) {
        std::cerr << err << std::endl;
    }
    std::cerr << "Compilation failed" << std::endl;
}

void output_code(const std::string& path, const std::string& code) {
    if (path.empty()) {
        std::cout << code;
    } else {
        std::ofstream file(path);
        file << code;
        file.close();
    }
}

void config_app(CLI::App& app) {
    app.add_option("-i,--input", in_path, "Input file path");
    app.add_option("-o,--output", out_path, "Output file path");
    app.add_option("-t,--target", out_target, "Output target (json, selenium, decompile)")
            ->check(CLI::IsMember({"json", "selenium", "decompile"}))->default_val("selenium");
    app.add_flag("--keep-xpath", keep_xpath,
                 "Keep XPATH instead of natural description (use this for testing purposes only)")->default_val(false);
}

int main(int argc, char** argv) {
    CLI::App app{"Restricted Natural Language Compiler"};
    argv = app.ensure_utf8(argv);
    config_app(app);

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return app.exit(e);
    }

    std::string file;

    if (in_path.empty()) {
        file = read_source(std::cin);
    } else {
        std::ifstream infile(in_path);
        if (infile.is_open()) {
            file = read_source(infile);
            infile.close();
        } else {
            std::cerr << "Could not find input file." << std::endl;
            return -1;
        }
    }

    parser p(std::move(file));
    decompiler r(std::move(file));
    auto res = out_target != "decompile" ? p.parse() : r.convert();

    if (res.has_value()) {
        const auto &tree = res.value();
        ASTVisitor *visitor;

        if (out_target == "json") {
            visitor = new JsonASTVisitor();
        } else if (out_target == "selenium") {
            visitor = new SeleniumASTVisitor(keep_xpath);
        } else if (out_target == "decompile"){
            visitor = new SourceASTVisitor();
        } else {
            std::cerr << "Invalid output target specified" << std::endl;
            return -1;
        }

        std::string code = tree.accept(*visitor);
        output_code(out_path, code);
    } else {
        show_errors(res.error());
    }

    return 0;
}