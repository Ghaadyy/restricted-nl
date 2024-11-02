#include "selenium.h"

// TODO
// IMPLEMENT ALL STATE: IS_DISPLAYED, HIDDEN, EQUAL
// WITH VALUE ??
// HANDLE ALERTS

void SeleniumCodeGen::init() {
    ss  << "const { Builder, Browser, By } = require('selenium-webdriver');" << std::endl;
    ss  << "const assert = require('assert');"     << std::endl;

    ss  << "function beforeTestHook() {}"       << std::endl;
    ss  << "function beforeEachTestHook() {}"   << std::endl;
    ss  << "function afterTestHook() {}"        << std::endl;
    ss  << "function afterEachTestHook() {}"    << std::endl;

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
}

void SeleniumCodeGen::createTest(const string& testName) {
    ss  << "it('" 
        << testName
        << "', async function () {" << std::endl
        << std::endl;
}

void SeleniumCodeGen::finishTest() {
    ss  << "});"
        << std::endl;
}

void SeleniumCodeGen::visit(const string& url) {
    ss << "await driver.get(" << url << ");" << std::endl;
}

void SeleniumCodeGen::click(const string& xpath) {
    ss  << "let element" << id << "= await driver.findElement(By.xpath("
        << xpath << "));"
        << std::endl;
    
    ss  << "await element" << id << ".click();"
        << std::endl; 
    id++;
}

void SeleniumCodeGen::hover(const string& xpath) {
    ss  << "let element" << id << "= await driver.findElement(By.xpath("
        << xpath << "));"
        << std::endl;
    
    ss  << "await element" << id << ".click();"
        << std::endl; 
    id++;
}

void SeleniumCodeGen::check(const string& xpath, const bool expectedValue) {
    ss  << "let element" << id << "= await driver.findElement(By.xpath("
        << xpath << "));"
        << std::endl;

    ss  << "let isDisplayed" << id << " = await element" << id << ".isDisplayed();"
        << std::endl
        << "assert.equal(isDisplayed" << id
        << ", " << (expectedValue ? "true" : "false")
        << ");"
        << std::endl;

    id++;
}

void SeleniumCodeGen::type(const string& xpath, const string& text) {
    ss  << "let element" << id << "= await driver.findElement(By.xpath("
        << xpath << "));"
        << std::endl;

    ss  << "await element" << id << ".sendKeys(" 
        << text 
        << ");" 
        << std::endl;
    id++;
}

string SeleniumCodeGen::generate() { 
    ss  << "});\n";
    return ss.str(); 
}