#include "selenium.h"

void SeleniumCodeGen::init() {
    ss  << "import { Builder, Browser, By } from \"selenium-webdriver\";" << std::endl;
    ss  << "import assert from \"assert\";" << std::endl;

    ss  << R"(describe('Script', function () {
    let driver;
    this.timeout(0);

    before(async function () {
        driver = await new Builder().forBrowser(Browser.CHROME).build();
        await driver.manage().setTimeouts({ implicit: 2147483647, pageLoad: 2147483647 });
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
    ss  << "after(async () => await driver.quit());\n});";
    return ss.str();
}