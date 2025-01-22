

# Class TestNode



[**ClassList**](annotated.md) **>** [**TestNode**](classTestNode.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  vector&lt; [**ActionNode**](classActionNode.md) \* &gt; | [**actions**](#variable-actions)  <br> |
|  string | [**testName**](#variable-testname)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  string | [**accept**](#function-accept) ([**ASTVisitor**](classASTVisitor.md) & visitor) const<br> |




























## Public Attributes Documentation




### variable actions 

```C++
vector<ActionNode*> TestNode::actions;
```




<hr>



### variable testName 

```C++
string TestNode::testName;
```




<hr>
## Public Functions Documentation




### function accept 

```C++
string TestNode::accept (
    ASTVisitor & visitor
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/ast/AST.h`

