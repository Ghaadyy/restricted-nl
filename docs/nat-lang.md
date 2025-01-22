# Natural Language Descriptions

## Smart Web Element Locators

Instead of relying on static locators such as XPATH, CSS classes or element IDs, the compiler identifies elements on a web page using a description of the element written in plain English (or Natural Language).

This is achieved by an external Large Vision-Language Model (LVLM). 
Our implementation uses [SeeClick](https://github.com/njucckevin/SeeClick) to get a pair `(x, y)` of coordinates indicating the location of the element on the web page.
SeeClick takes as input the image of the current web page as well as the description specified by the user.

In this example, the NL description of the user is `"sign in present in the top right corner`.
This is passed along with a screenshot of the web page to SeeClick. It then resolves a pair of coordinates which can be used to move to this location and perform actions on the located element.

```
click link with description "sign in present in the top right corner"
```