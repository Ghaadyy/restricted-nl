

# File parser.cpp



[**FileList**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**parser.cpp**](parser_8cpp.md)

[Go to the source code of this file](parser_8cpp_source.md)



* `#include "parser.h"`
* `#include <cstring>`
* `#include "ast/SeleniumASTVisitor.h"`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  DLL\_API bool | [**parse**](#function-parse) (const char \* path, const char \*\* code, const char \*\* errors, size\_t \* error\_count) <br> |



























## Macros

| Type | Name |
| ---: | :--- |
| define  | [**DLL\_API**](parser_8cpp.md#define-dll_api)  `\_\_attribute\_\_((visibility("default")))`<br> |

## Public Functions Documentation




### function parse 

```C++
DLL_API bool parse (
    const char * path,
    const char ** code,
    const char ** errors,
    size_t * error_count
) 
```




<hr>
## Macro Definition Documentation





### define DLL\_API 

```C++
#define DLL_API `__attribute__((visibility("default")))`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/parser.cpp`

