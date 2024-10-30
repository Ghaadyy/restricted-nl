#include "selenium.h"

// TODO
// IMPLEMENT ALL STATE: IS_DISPLAYED, HIDDEN, EQUAL
// WITH VALUE ??

void SeleniumCodeGen::init() {
    ss  << "import { Builder, Browser, By } from \"selenium-webdriver\";" << std::endl;
    ss  << "import assert from \"assert\";" << std::endl;
    ss  << "import websocket from \"websocket\";" << std::endl;
    ss  << "const { w3cwebsocket: WebSocket } = websocket;" << std::endl;

    ss  << R"(
    function sendAssert(socket, test) {
        if (socket.readyState == socket.OPEN) {
            socket.send(JSON.stringify(test));
        }
    }

    describe('Script', function () {
        let driver;
        let socket;
        this.timeout(0);

        before(async function () {
            driver = await new Builder().forBrowser(Browser.CHROME).build();
            socket = new WebSocket("ws://localhost:5064/ws/selenium");
            await driver.manage().setTimeouts({ implicit: 2147483647, pageLoad: 2147483647 });

            socket.onopen = async function () {
                console.log("open");
            };

            socket.onerror = function (err) {
                console.log("Error here!!!");
                console.log(err.message);
            };

            socket.onclose = function (event) {
                console.log(event.reason);
            };
        });

        afterEach(function () {
            sendAssert(socket, {
                testName: this.currentTest.title,
                passed: this.currentTest.state === "passed",
            });
        });

        after(async () => {
            await driver.quit();
        });

        after(() => socket.close());)"
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