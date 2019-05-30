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

12. parameter_id_list  -> parameter_id | parameter_id , parameter_id_list 

13. parameter_id -> **IDENTIFIER** |  **IDENTIFIER** [NUMBER]

    

14. compound_statement -> { local_declarations  statement_list }

15. local_declarations -> local_declarations scoped_variable_declaration | *epsilon* 
