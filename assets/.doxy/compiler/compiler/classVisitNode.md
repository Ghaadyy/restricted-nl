

# Class VisitNode



[**ClassList**](annotated.md) **>** [**VisitNode**](classVisitNode.md)








Inherits the following classes: [ActionNode](classActionNode.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**VisitNode**](#function-visitnode) (string && url) <br> |
| virtual string | [**accept**](#function-accept) ([**ASTVisitor**](classASTVisitor.md) & visitor) override const<br> |
|  string | [**get\_url**](#function-get_url) () const<br> |


## Public Functions inherited from ActionNode

See [ActionNode](classActionNode.md)

| Type | Name |
| ---: | :--- |
|   | [**ActionNode**](classActionNode.md#function-actionnode) () = default<br> |
| virtual string | [**accept**](classActionNode.md#function-accept) ([**ASTVisitor**](classASTVisitor.md) & visitor) const = 0<br> |






















































## Public Functions Documentation




### function VisitNode 

```C++
explicit VisitNode::VisitNode (
    string && url
) 
```




<hr>



### function accept 

```C++
virtual string VisitNode::accept (
    ASTVisitor & visitor
) override const
```



Implements [*ActionNode::accept*](classActionNode.md#function-accept)


<hr>



### function get\_url 

```C++
inline string VisitNode::get_url () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/ast/AST.h`

