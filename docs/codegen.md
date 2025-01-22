# Adding a Code Generator

Currently, our compiler supports generating code for the [Selenium](https://www.selenium.dev) library. We also have the option to serialize the Abstract Syntax Tree (AST) to JSON. 

## The Visitor Pattern

Our implementation should be straightforward if you are already familiar with the Visitor design pattern.

- The JSON serializer is done though the `JsonASTVisitor`
- The Selenium codegen is done through the `SeleniumASTVisitor`

## Serialized AST with JSON

The GitHub example present in the [home page](index.md) produces the following JSON output.
This feature is useful if you aim to use this compiler within another project to represent this test visually as seen [here](https://github.com/Ghaadyy/fyp).

```json
{
  "tests": [
    {
      "actions": [
        { "type": "VisitNode", "url": "\"https://github.com\"" },
        {
          "description": "\"sign in present in the top right corner\"",
          "element_type": "link",
          "type": "ClickNode"
        },
        {
          "description": "\"GitHub logo\"",
          "element_type": "image",
          "state": true,
          "type": "CheckNode"
        },
        {
          "content": "\"johndoe\"",
          "description": "\"the username input field\"",
          "element_type": "input",
          "type": "TypeNode"
        },
        {
          "content": "\"secretpassword\"",
          "description": "\"the password input filed\"",
          "element_type": "input",
          "type": "TypeNode"
        },
        {
          "description": "\"sign in button\"",
          "element_type": "button",
          "type": "ClickNode"
        }
      ],
      "testName": "githubSignIn",
      "type": "TestNode"
    }
  ],
  "type": "AST"
}
```

## Supporting a New Target

To generate code for an unsupported library or format, you can create a new visitor class for your target which implements the `ASTVisitor` interface.

To achieve this you have to implement the following functions:

```cpp
class ASTVisitor {
public:
    virtual string visit(const VisitNode& node) = 0;
    virtual string visit(const ClickNode& node) = 0;
    virtual string visit(const TypeNode& node) = 0;
    virtual string visit(const CheckNode& node) = 0;
    virtual string visit(const TestNode& node) = 0;
    virtual string visit(const AST& tree) = 0;
};
```
