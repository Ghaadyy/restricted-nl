

# Class TypeNode



[**ClassList**](annotated.md) **>** [**TypeNode**](classTypeNode.md)








Inherits the following classes: [ActionNode](classActionNode.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TypeNode**](#function-typenode) (string && content, string && element\_type, string && description) <br> |
| virtual string | [**accept**](#function-accept) ([**ASTVisitor**](classASTVisitor.md) & visitor) override const<br> |
|  string | [**get\_content**](#function-get_content) () const<br> |
|  string | [**get\_description**](#function-get_description) () const<br> |
|  string | [**get\_element\_type**](#function-get_element_type) () const<br> |


## Public Functions inherited from ActionNode

See [ActionNode](classActionNode.md)

| Type | Name |
| ---: | :--- |
|   | [**ActionNode**](classActionNode.md#function-actionnode) () = default<br> |
| virtual string | [**accept**](classActionNode.md#function-accept) ([**ASTVisitor**](classASTVisitor.md) & visitor) const = 0<br> |






















































## Public Functions Documentation




### function TypeNode 

```C++
explicit TypeNode::TypeNode (
    string && content,
    string && element_type,
    string && description
) 
```




<hr>



### function accept 

```C++
virtual string TypeNode::accept (
    ASTVisitor & visitor
) override const
```



Implements [*ActionNode::accept*](classActionNode.md#function-accept)


<hr>



### function get\_content 

```C++
string TypeNode::get_content () const
```




<hr>



### function get\_description 

```C++
string TypeNode::get_description () const
```




<hr>



### function get\_element\_type 

```C++
string TypeNode::get_element_type () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/ast/AST.h`

