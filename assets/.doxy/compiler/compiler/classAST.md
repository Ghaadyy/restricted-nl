

# Class AST



[**ClassList**](annotated.md) **>** [**AST**](classAST.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  vector&lt; [**TestNode**](classTestNode.md) &gt; | [**tests**](#variable-tests)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AST**](#function-ast-12) (vector&lt; [**TestNode**](classTestNode.md) &gt; tests) <br> |
|   | [**AST**](#function-ast-22) () <br> |
|  string | [**accept**](#function-accept) ([**ASTVisitor**](classASTVisitor.md) & visitor) const<br> |




























## Public Attributes Documentation




### variable tests 

```C++
vector<TestNode> AST::tests;
```




<hr>
## Public Functions Documentation




### function AST [1/2]

```C++
explicit AST::AST (
    vector< TestNode > tests
) 
```




<hr>



### function AST [2/2]

```C++
explicit AST::AST () 
```




<hr>



### function accept 

```C++
string AST::accept (
    ASTVisitor & visitor
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/ast/AST.h`

