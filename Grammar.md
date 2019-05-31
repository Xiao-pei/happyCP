## The Grammar

------

Expressions

1. program -> declaration_list
2. declaration_list -> declaration  declaration_list | declaration
3. postfix_expression -> primary-expression | postfix_expression ( ) | postfix_expression (argument_expression_list) | postfix_expression.**IDENTIFIER** | postfix_expression **INCREMENT** | postfix_expression **DECREMENT**
4. primary_expression -> **IDENTIFIER**


Declarations

4. declaration  -> variable_declaration | function_declaration | enum_declaration

5. variable_declaration -> type_specifier; | declaration_specifiers variable_declaration_list;

6. variable_declarator_list -> variable_declarator_list, direct_declarator | direct_declarator 

7. direct_declarator  -> **IDENTIFIER** | **IDENTIFIER** [**NUMBER**] | (direct_declarator)

8. type_specifier -> **VOID** | **CHAR** | **INT** | **FLOAT** | **DOUBLE** | **BOOL**

   

9. function_declaration -> type_specifier **IDENTIFIER** ( parameters ) compound_statement

10. parameters -> parameter_list | *epsilon*

11. parameter_list -> type_specifier parameter_id_list |  parameter_list, type_specifier parameter_id_list

12. parameter_id_list  -> parameter_id | parameter_id_list , parameter_id

13. parameter_id -> **IDENTIFIER** |  **IDENTIFIER** [ ]

    

14. compound_statement -> { declaration_list  statement_list } | ;

15. declaration_list  -> declaration  | declaration_list  declaration 

16. statement_list -> *epsilon* | statement statement_list 

17. statement  ->   expression_statement| compound_statement |  expression_statement  | jump_statement | iteration_statement |   selection_statement 

18. iteration_statement  -> **WHILE** ( expression ) statement 

19.  selection_statement  -> **IF** ( expression ) statement | **IF** ( expression ) statement  **ELSE** statement 

