

# Class CheckNode



[**ClassList**](annotated.md) **>** [**CheckNode**](classCheckNode.md)








Inherits the following classes: [ActionNode](classActionNode.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CheckNode**](#function-checknode) (string && element\_type, string && description, bool state) <br> |
| virtual string | [**accept**](#function-accept) ([**ASTVisitor**](classASTVisitor.md) & visitor) override const<br> |
|  string | [**get\_description**](#function-get_description) () const<br> |
|  string | [**get\_element\_type**](#function-get_element_type) () const<br> |
|  bool | [**get\_state**](#function-get_state) () const<br> |


## Public Functions inherited from ActionNode

See [ActionNode](classActionNode.md)

| Type | Name |
| ---: | :--- |
|   | [**ActionNode**](classActionNode.md#function-actionnode) () = default<br> |
| virtual string | [**accept**](classActionNode.md#function-accept) ([**ASTVisitor**](classASTVisitor.md) & visitor) const = 0<br> |






















































## Public Functions Documentation




### function CheckNode 

```C++
explicit CheckNode::CheckNode (
    string && element_type,
    string && description,
    bool state
) 
```




<hr>



### function accept 

```C++
virtual string CheckNode::accept (
    ASTVisitor & visitor
) override const
```



Implements [*ActionNode::accept*](classActionNode.md#function-accept)


<hr>



### function get\_description 

```C++
string CheckNode::get_description () const
```




<hr>



### function get\_element\_type 

```C++
string CheckNode::get_element_type () const
```




<hr>



### function get\_state 

```C++
bool CheckNode::get_state () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/ast/AST.h`

