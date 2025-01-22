

# Class ASTVisitor



[**ClassList**](annotated.md) **>** [**ASTVisitor**](classASTVisitor.md)










Inherited by the following classes: [JsonASTVisitor](classJsonASTVisitor.md),  [SeleniumASTVisitor](classSeleniumASTVisitor.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual string | [**visit**](#function-visit-16) (const [**VisitNode**](classVisitNode.md) & node) = 0<br> |
| virtual string | [**visit**](#function-visit-26) (const [**ClickNode**](classClickNode.md) & node) = 0<br> |
| virtual string | [**visit**](#function-visit-36) (const [**TypeNode**](classTypeNode.md) & node) = 0<br> |
| virtual string | [**visit**](#function-visit-46) (const [**CheckNode**](classCheckNode.md) & node) = 0<br> |
| virtual string | [**visit**](#function-visit-56) (const [**TestNode**](classTestNode.md) & node) = 0<br> |
| virtual string | [**visit**](#function-visit-66) (const [**AST**](classAST.md) & tree) = 0<br> |




























## Public Functions Documentation




### function visit [1/6]

```C++
virtual string ASTVisitor::visit (
    const VisitNode & node
) = 0
```




<hr>



### function visit [2/6]

```C++
virtual string ASTVisitor::visit (
    const ClickNode & node
) = 0
```




<hr>



### function visit [3/6]

```C++
virtual string ASTVisitor::visit (
    const TypeNode & node
) = 0
```




<hr>



### function visit [4/6]

```C++
virtual string ASTVisitor::visit (
    const CheckNode & node
) = 0
```




<hr>



### function visit [5/6]

```C++
virtual string ASTVisitor::visit (
    const TestNode & node
) = 0
```




<hr>



### function visit [6/6]

```C++
virtual string ASTVisitor::visit (
    const AST & tree
) = 0
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/ast/AST.h`

