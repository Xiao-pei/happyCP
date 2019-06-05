## The Grammar

1. program -> declaration_list
2. declaration_list -> declaration  declaration_list | declaration

### Declarations

4. declaration  -> variable_declaration | function_declaration | enum_declaration

5. variable_declaration -> type_specifier**;** | declaration_specifiers variable_declaration_list**;**

6. variable_declarator_list -> variable_declarator_list**,** direct_declarator | direct_declarator 

7. direct_declarator  -> **IDENTIFIER** | **IDENTIFIER** **[NUMBER]** | **(**direct_declarator**)**

8. type_specifier -> **VOID** | **CHAR** | **INT** | **FLOAT** | **DOUBLE** | **BOOL**

   

9. function_declaration -> type_specifier **IDENTIFIER** **(** parameters **)** compound_statement

10. parameters -> parameter_list | *epsilon*

11. parameter_list -> type_specifier parameter_id_list |  parameter_list, type_specifier parameter_id_list

12. parameter_id_list  -> parameter_id | parameter_id_list , parameter_id

13. parameter_id -> **IDENTIFIER** |  **IDENTIFIER** **[ ]**

### Statement

14. compound_statement -> **{** declaration_list  statement_list **}** | **;**
15. declaration_list  -> declaration  | declaration_list  declaration 
16. statement_list -> ***epsilon*** | statement statement_list 
17. statement  ->   expression_statement | compound_statement |  expression_statement  | jump_statement | iteration_statement |  selection_statement 
18. iteration_statement  -> **WHILE** **(** expression **)** statement |  **DO** statement **WHILE** **(** expression **)** | **FOR** **(** expression **;** expression **;** expression **)** statement 
20. selection_statement  -> **IF** **(** expression **)** statement | **IF** **(** expression **)** statement  **ELSE** statement 
21. expression_statement -> expression**;** | **;**
22. jump_statement -> **BREAK**; | **RETURN** expression**;** | **RETURN** **;** | **CONTINUE ;**

### Expression

22. expression -> assignment_expression | expression,  assignment_expression
23. assignment_expression -> unary_expression assignment_operator assignment_expression | logical_OR_expression
24. assignment_operator -> **=**
25. logical_OR_expression -> logical_AND_expression | logical_OR_expression **||** logical_AND_expression
26. logical_AND_expression -> inclusive_OR_expression | logical_AND_expression **&&** inclusive_OR_expression
27. inclusive_OR_expression -> exclusive_OR_expression | inclusive_OR_expression **|** exclusive_OR_expression
28. exclusive_OR_expression -> AND_expression | exclusive_OR_expression **^** AND_expression
29. AND_expression -> equality_expression | AND_expression **&** equality_expression
30. equality_expression -> relational_expression | equality_expression **==** relational_expression | equality_expression **!=** relational_expression
31. relational_expression -> relational_expression **<** additive_expression | relational_expression **>** additive_expression | additive_expression
32. additive_expression -> multiplicative_expression | additive_expression **+** multiplicative_expression | additive_expression **-** multiplicative_expression
33. multiplicative_expression -> unary_expression | multiplicative_expression ***** unary_expression | multiplicative_expression **/** unary_expression
34. unary_expression -> postfix_expression | **++** unary_expression | **--** unary_expression | **!** 
35. postfix_expression -> primary-expression | postfix_expression **( )** | postfix_expression **(**argument_expression_list**)** | postfix_expression.**IDENTIFIER** | postfix_expression **++** | postfix_expression **--** | postfix_expression **[**expression**]**
36. argument_expression_list -> argument_expression | argument_expression_list **, **argument_expression
37. primary_expression -> **IDENTIFIER** | **(** expression **)**

