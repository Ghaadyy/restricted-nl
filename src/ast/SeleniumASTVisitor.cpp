#include "SeleniumASTVisitor.h"
#include <sstream>

string SeleniumASTVisitor::visit(const VisitNode &node) {
    stringstream ss;
    ss << "await driver.get(" << node.get_url() << ");" << std::endl;
    return ss.str();
}

string SeleniumASTVisitor::visit(const ClickNode &node) {
    stringstream ss;
    ss  << "let element" << id << "= await driver.findElement(By.xpath("
        << node.get_description() << "));"
        << std::endl;

    ss  << "await element" << id << ".click();"
        << std::endl;
    id++;
    return ss.str();
}

string SeleniumASTVisitor::visit(const TypeNode &node) {
    stringstream ss;
    ss  << "let element" << id << "= await driver.findElement(By.xpath("
        << node.get_description() << "));"
        << std::endl;

    ss  << "await element" << id << ".sendKeys("
        << node.get_content()
        << ");"
        << std::endl;
    id++;
    return ss.str();
}

string SeleniumASTVisitor::visit(const CheckNode &node) {
    stringstream ss;
    ss  << "let element" << id << "= await driver.findElement(By.xpath("
        << node.get_description() << "));"
        << std::endl;

    ss  << "let isDisplayed" << id << " = await element" << id << ".isDisplayed();"
        << std::endl
        << "assert.equal(isDisplayed" << id
        << ", " << (node.get_state() ? "true" : "false")
        << ");"
        << std::endl;
    id++;
    return ss.str();
}

string SeleniumASTVisitor::visit(const TestNode &node) {
    stringstream ss;

    ss  << "it('"
        << node.testName
        << "', async function () {" << std::endl
        << std::endl;

    for(auto& action : node.actions) {
        ss << action->accept(*this);
    }

    ss  << "});" << std::endl;

    return ss.str();
}

string SeleniumASTVisitor::visit(const AST &tree) {
    stringstream ss;

    ss  << "const { Builder, Browser, By } = require('selenium-webdriver');"    << std::endl;
    ss  << "const assert = require('assert');"                                  << std::endl;

    ss  << "function beforeTestHook() {}"                                       << std::endl;
    ss  << "function beforeEachTestHook() {}"                                   << std::endl;
    ss  << "function afterTestHook() {}"                                        << std::endl;
    ss  << "function afterEachTestHook() {}"                                    << std::endl;

    ss  << R"(describe("Script", function () {
  let driver;
  this.timeout(0);

  before(beforeTestHook);
  beforeEach(beforeEachTestHook);
  after(afterTestHook);
  afterEach(afterEachTestHook);

  before(async function () {
    driver = await new Builder().forBrowser(Browser.CHROME).build();
    await driver
      .manage()
      .setTimeouts({ implicit: 2147483647, pageLoad: 2147483647 });
  });

  after(async () => {
    await driver.quit();
  });)"
        << std::endl;

    for(auto& test : tree.tests) {
        ss << test.accept(*this);
    }

    ss  << "});\n";

    return ss.str();
}
