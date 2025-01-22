

# Class Scanner



[**ClassList**](annotated.md) **>** [**Scanner**](classScanner.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Scanner**](#function-scanner) (string && content) <br> |
|  int | [**line\_number**](#function-line_number) () const<br> |
|  int | [**yylex**](#function-yylex) () <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  string | [**getTokenName**](#function-gettokenname) (int tokenId) <br> |


























## Public Functions Documentation




### function Scanner 

```C++
explicit Scanner::Scanner (
    string && content
) 
```




<hr>



### function line\_number 

```C++
int Scanner::line_number () const
```




<hr>



### function yylex 

```C++
int Scanner::yylex () 
```




<hr>
## Public Static Functions Documentation




### function getTokenName 

```C++
static string Scanner::getTokenName (
    int tokenId
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/scanner.h`

