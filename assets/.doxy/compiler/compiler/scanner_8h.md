

# File scanner.h



[**FileList**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**scanner.h**](scanner_8h.md)

[Go to the source code of this file](scanner_8h_source.md)



* `#include <string>`
* `#include <map>`
* `#include <functional>`
* `#include <iostream>`
* `#include <fstream>`
* `#include <regex>`
* `#include <vector>`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**Scanner**](classScanner.md) <br> |
| struct | [**lex\_rule**](structlex__rule.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**Tokens**](#enum-tokens)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  string | [**yysval**](#variable-yysval)  <br> |












































## Public Types Documentation




### enum Tokens 

```C++
enum Tokens {
    TEST_NAME = 257,
    CLICK,
    VISIT,
    BUTTON,
    LINK,
    TEXT,
    IMAGE,
    DISPLAYED,
    HIDDEN,
    CHECK_IF,
    WITH_DESC,
    HOVER_OVER,
    NLD,
    URL,
    ON,
    TYPE,
    CONTENT,
    LEFT_BRACE,
    RIGHT_BRACE,
    INPUT
};
```




<hr>
## Public Attributes Documentation




### variable yysval 

```C++
string yysval;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/scanner.h`

