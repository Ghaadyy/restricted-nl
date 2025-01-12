#include "SeleniumASTVisitor.h"
#include <sstream>

string SeleniumASTVisitor::visit(const VisitNode &node) {
    stringstream ss;
    ss << "await driver.get(" << node.get_url() << ");" << std::endl;
    return ss.str();
}

string SeleniumASTVisitor::visit(const ClickNode &node) {
    stringstream ss;
    ss << "await clickNode(browsingContext, driver, " << node.get_description() << ");" << std::endl;
    return ss.str();
}

string SeleniumASTVisitor::visit(const TypeNode &node) {
    stringstream ss;
    ss << "await typeNode(browsingContext, driver, " << node.get_description() << ", " << node.get_content() << ");" << std::endl;
    return ss.str();
}

string SeleniumASTVisitor::visit(const CheckNode &node) {
    stringstream ss;
    string state = (node.get_state() ? "true" : "false");
    ss << "assert.equal(await checkNode(browsingContext, driver, \"" << node.get_element_type() << "\", " << node.get_description() << ", " << state << ", title), " << state  << ");" << std::endl;
    return ss.str();
}

string SeleniumASTVisitor::visit(const TestNode &node) {
    stringstream ss;

    ss  << "it('"
        << node.testName
        << "', async function () {" << std::endl
        << "const title = '" << node.testName << "';"
        << std::endl;

    for(auto& action : node.actions) {
        ss << action->accept(*this);
    }

    ss  << "});" << std::endl;

    return ss.str();
}

string SeleniumASTVisitor::visit(const AST &tree) {
    stringstream ss;

    ss  << "const { Builder, Browser, By } = require('selenium-webdriver');"                << std::endl;
    ss  << "const assert = require('assert');"                                              << std::endl;
    ss  << "const BrowsingContext = require(\"selenium-webdriver/bidi/browsingContext\");"  << std::endl;
    ss  << "const chrome = require(\"selenium-webdriver/chrome\");"                         << std::endl;
    ss  << "const fs = require(\"fs\");"                                                    << std::endl;

    ss  << "function beforeHook() {}"                                                   << std::endl;
    ss  << "function beforeEachHook() {}"                                               << std::endl;
    ss  << "function afterHook() {}"                                                    << std::endl;
    ss  << "function afterEachHook() {}"                                                << std::endl;
    ss  << "function afterEachAssertHook() {}"                                              << std::endl;
    ss  << "function getToken() {}"                                                         << std::endl;
    ss  << "function getServerURL() {}"                                                     << std::endl;

    ss << R"(async function getCoordinates(browsingContext, description) {
        try {
            const res = await fetch(getServerURL(), {
                method: "POST",
                headers: {
                    "Content-Type": "application/json",
                    "Authorization": `Bearer ${getToken()}`
                },
                body: JSON.stringify({
                    image: await browsingContext.captureScreenshot(),
                    description: description,
                }),
            });

            const data = await res.json();

            if (res.ok) {
                return data;
            } else {
                throw new Error("Error in fetching coordinates");
            }
        } catch (error) {
            throw new Error("Error in fetching coordinates");
        }
    })" << std::endl;

    ss << R"(async function elementFromPoint(driver, x, y) {
      return await driver.executeScript(
        "return document.elementFromPoint(arguments[0], arguments[1]);",
        x,
        y
      );
    })" << std::endl;

    ss << R"(async function clickNode(browsingContext, driver, description) {
        const [x, y] = await getCoordinates(browsingContext, description);
        const actions = driver.actions({ async: true });
        await actions.move({ x, y }).click().perform();
    })" << std::endl;
    ss << R"(async function typeNode(browsingContext, driver, description, content) {
        const [x, y] = await getCoordinates(browsingContext, description);
        const actions = driver.actions({ async: true });
        await actions.move({ x, y }).click().sendKeys(content).perform();
    })" << std::endl;
        ss << R"(async function checkNode(browsingContext, driver, element_type, description, state, test) {
        const [x, y] = await getCoordinates(browsingContext, description);
        let element = await elementFromPoint(driver, x, y);
        let isDisplayed = await element.isDisplayed();
        await afterEachAssertHook(`${element_type} with description "${description}" should be ${state ? 'displayed' : 'hidden'}`, isDisplayed == state, test);
        return isDisplayed;
    })" << std::endl;

    ss  << R"(describe("Script", function () {
  let driver;
  let id;
  let browsingContext;
  this.timeout(0);

  before(beforeHook);
  beforeEach(beforeEachHook);
  after(afterHook);
  afterEach(afterEachHook);

  before(async function () {
    driver = await new Builder().forBrowser(Browser.CHROME)
        .setChromeOptions(new chrome.Options().enableBidi())
        .build();
    await driver
      .manage()
      .setTimeouts({ implicit: 2147483647, pageLoad: 2147483647 });
    id = await driver.getWindowHandle();
    browsingContext = await BrowsingContext(driver, {
        browsingContextId: id,
    });
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
