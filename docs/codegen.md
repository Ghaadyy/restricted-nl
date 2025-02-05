# Adding a Code Generator

Currently, our compiler supports generating code for the [Selenium](https://www.selenium.dev) library. We also have the option to serialize the Abstract Syntax Tree (AST) to JSON. 

## The Visitor Pattern

Our implementation should be straightforward if you are already familiar with the Visitor design pattern.

- The `JsonASTVisitor` serializer translates the source code's AST into a JSON format
- The Selenium code generation is achieved by the `SeleniumASTVisitor`
- The Decompiler visitor `DecompilerASTVisitor` to generate the corresponding source code from a serialized AST 

## Serialized AST with JSON

Compiling he GitHub example present in the [home page](index.md) with `rnlc -t json` produces the following JSON output.
This feature is useful if you aim to use this compiler within another project to represent this test visually as seen [here](https://github.com/Ghaadyy/fyp).

```json
{
  "tests": [
    {
      "actions": [
        { "action": "visit", "url": "https://github.com" },
        {
          "action": "click",
          "description": "sign in present in the top right corner",
          "elementType": "link"
        },
        {
          "action": "check",
          "description": "GitHub logo",
          "elementType": "image",
          "state": true
        },
        {
          "action": "type",
          "content": "johndoe",
          "description": "the username input field",
          "elementType": "input"
        },
        {
          "action": "type",
          "content": "secretpassword",
          "description": "the password input filed",
          "elementType": "input"
        },
        {
          "action": "click",
          "description": "sign in button",
          "elementType": "button"
        }
      ],
      "testName": "githubSignIn"
    }
  ]
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
