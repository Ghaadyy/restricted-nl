

# Class JsonASTVisitor



[**ClassList**](annotated.md) **>** [**JsonASTVisitor**](classJsonASTVisitor.md)








Inherits the following classes: [ASTVisitor](classASTVisitor.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual string | [**visit**](#function-visit-16) (const [**VisitNode**](classVisitNode.md) & node) override<br> |
| virtual string | [**visit**](#function-visit-26) (const [**ClickNode**](classClickNode.md) & node) override<br> |
| virtual string | [**visit**](#function-visit-36) (const [**TypeNode**](classTypeNode.md) & node) override<br> |
| virtual string | [**visit**](#function-visit-46) (const [**CheckNode**](classCheckNode.md) & node) override<br> |
| virtual string | [**visit**](#function-visit-56) (const [**TestNode**](classTestNode.md) & node) override<br> |
| virtual string | [**visit**](#function-visit-66) (const [**AST**](classAST.md) & tree) override<br> |


## Public Functions inherited from ASTVisitor

See [ASTVisitor](classASTVisitor.md)

| Type | Name |
| ---: | :--- |
| virtual string | [**visit**](classASTVisitor.md#function-visit-16) (const [**VisitNode**](classVisitNode.md) & node) = 0<br> |
| virtual string | [**visit**](classASTVisitor.md#function-visit-26) (const [**ClickNode**](classClickNode.md) & node) = 0<br> |
| virtual string | [**visit**](classASTVisitor.md#function-visit-36) (const [**TypeNode**](classTypeNode.md) & node) = 0<br> |
| virtual string | [**visit**](classASTVisitor.md#function-visit-46) (const [**CheckNode**](classCheckNode.md) & node) = 0<br> |
| virtual string | [**visit**](classASTVisitor.md#function-visit-56) (const [**TestNode**](classTestNode.md) & node) = 0<br> |
| virtual string | [**visit**](classASTVisitor.md#function-visit-66) (const [**AST**](classAST.md) & tree) = 0<br> |






















































## Public Functions Documentation




### function visit [1/6]

```C++
virtual string JsonASTVisitor::visit (
    const VisitNode & node
) override
```



Implements [*ASTVisitor::visit*](classASTVisitor.md#function-visit-16)


<hr>



### function visit [2/6]

```C++
virtual string JsonASTVisitor::visit (
    const ClickNode & node
) override
```



Implements [*ASTVisitor::visit*](classASTVisitor.md#function-visit-26)


<hr>



### function visit [3/6]

```C++
virtual string JsonASTVisitor::visit (
    const TypeNode & node
) override
```



Implements [*ASTVisitor::visit*](classASTVisitor.md#function-visit-36)


<hr>



### function visit [4/6]

```C++
virtual string JsonASTVisitor::visit (
    const CheckNode & node
) override
```



Implements [*ASTVisitor::visit*](classASTVisitor.md#function-visit-46)


<hr>



### function visit [5/6]

```C++
virtual string JsonASTVisitor::visit (
    const TestNode & node
) override
```



Implements [*ASTVisitor::visit*](classASTVisitor.md#function-visit-56)


<hr>



### function visit [6/6]

```C++
virtual string JsonASTVisitor::visit (
    const AST & tree
) override
```



Implements [*ASTVisitor::visit*](classASTVisitor.md#function-visit-66)


<hr>

------------------------------
The documentation for this class was generated from the following file `src/ast/JsonASTVisitor.h`

