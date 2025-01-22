

# Class ClickNode



[**ClassList**](annotated.md) **>** [**ClickNode**](classClickNode.md)








Inherits the following classes: [ActionNode](classActionNode.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ClickNode**](#function-clicknode) (string && element\_type, string && description) <br> |
| virtual string | [**accept**](#function-accept) ([**ASTVisitor**](classASTVisitor.md) & visitor) override const<br> |
|  string | [**get\_description**](#function-get_description) () const<br> |
|  string | [**get\_element\_type**](#function-get_element_type) () const<br> |


## Public Functions inherited from ActionNode

See [ActionNode](classActionNode.md)

| Type | Name |
| ---: | :--- |
|   | [**ActionNode**](classActionNode.md#function-actionnode) () = default<br> |
| virtual string | [**accept**](classActionNode.md#function-accept) ([**ASTVisitor**](classASTVisitor.md) & visitor) const = 0<br> |






















































## Public Functions Documentation




### function ClickNode 

```C++
explicit ClickNode::ClickNode (
    string && element_type,
    string && description
) 
```




<hr>



### function accept 

```C++
virtual string ClickNode::accept (
    ASTVisitor & visitor
) override const
```



Implements [*ActionNode::accept*](classActionNode.md#function-accept)


<hr>



### function get\_description 

```C++
string ClickNode::get_description () const
```




<hr>



### function get\_element\_type 

```C++
string ClickNode::get_element_type () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/ast/AST.h`

