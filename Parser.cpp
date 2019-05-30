#include "Parser.h"

Parser::Parser(Lexical* l)
{
	lexial = l;
	root_node = nullptr;
	current = nullptr;
}

void Parser::Parse()
{
	Program();
}

void Parser::SyntaxError(string s)
{
	cout << "\x1b[31mError:\033[0m " + s << endl;
	cout << current->to_string() << endl;
}

void Parser::Match(TokenType t)
{
	Token* p = current;
	if (current->token_type == t)
	{
		current = lexial->get_token();
		cout << current->to_string() << endl;
		delete p;
	}
	else
	{
		SyntaxError("unexpected token");
	}
}

void Parser::Program()
{
	current = lexial->get_token();
	DeclarationList();
}

void Parser::DeclarationList()
{
	Declaration(root_node);
	TreeNode* current_node = root_node;
	while (current->token_type != ENDOFFILE && current->token_type != ELSE)
	{
		if (root_node != nullptr)
			Declaration(current_node->sibling);
		else
			Declaration(root_node);
	}
}

void Parser::Declaration(TreeNode* & current_node)
{
	TokenType base_type = ERROR;
	TreeNodeKind default_kind = VARIABLE_DECLARTION;
	current_node = new TreeNode();
	switch (current->token_type)
	{
	case VOID:
		Match(VOID);
		base_type = VOID;
		current_node->token_type = IDENTIFIER;
		current_node->token_name = current->name;
		current_node->description = "Function declaration";
		current_node->left_child = new TreeNode(base_type);
		Match(IDENTIFIER);
		FunctionDeclaration(current_node->right_child);
		break;
	case CHAR:
		Match(CHAR);
		base_type = CHAR;
		break;
	case INT:
		Match(INT);
		base_type = INT;
		break;
	case FLOAT:
		Match(FLOAT);
		base_type = FLOAT;
		break;
	case DOUBLE:
		Match(DOUBLE);
		base_type = DOUBLE;
		break;
	case BOOL:
		Match(BOOL);
		base_type = BOOL;
		break;
	}
	if (current->token_type == SEMICOLON)
	{
		Match(SEMICOLON);
		current_node->description = "Empty declartion";
	}
	else if (current->token_type == LPAREN)
	{
		current_node->kind = VARIABLE_DECLARTION;
		current_node->description = "Variable declartion";
		VariableDeclaratorList(current_node);
	}
	else //could be function declartion or variable declartion 
	{
		string token_name = current->name;
		Match(IDENTIFIER);
		if (current->token_type == LPAREN)
			// function tree node holds the function ID, left child holds the return type.
		{
			current_node->token_type = IDENTIFIER;
			current_node->token_name = token_name;
			current_node->description = "Function declaration";
			current_node->left_child = new TreeNode(base_type);
			FunctionDeclaration(current_node->right_child);
		}

		else //the leftchild holds variable type, and rightchild holds declarators
		{
			current_node->kind = VARIABLE_DECLARTION;
			current_node->left_child = new TreeNode(base_type);
			current_node->description = "Variable declaration";
			current_node->right_child = new TreeNode(IDENTIFIER, token_name);
			VariableDeclaratorList(current_node);
		}
	}
	if (current->token_type == SEMICOLON)
		Match(SEMICOLON);
	else
		SyntaxError("Expect ; behind a declaration");
}

void Parser::VariableDeclaratorList(TreeNode* & current_node)
{
	if (current_node == nullptr)
	{
		SyntaxError("Variable Difination Error");
		return;
	}
	else //variable_declarator_list, direct_declarator| direct_declarator
	{
		TreeNode* variable_treenode = current_node->right_child;
		if (variable_treenode == nullptr)
			DirectDeclarator(variable_treenode);
		else
			DirectDeclarator(variable_treenode->sibling);
		while (current->token_type == COMMA)
		{
			Match(COMMA);
			variable_treenode = variable_treenode->sibling;
			DirectDeclarator(current_node->right_child->sibling);
		}
	}
}

//parse IDENTIFIER|IDENTIFIER[NUMBER]|(direct_declarator) list
void Parser::DirectDeclarator(TreeNode* & current_node)
{
	if (current->token_type == IDENTIFIER)
	{
		string identifier_name = current->name;
		Match(IDENTIFIER);
		if (current->token_type == LBRACKET)
		{
			Match(LBRACKET);
			// Array node: left child holds id, and right child holds the number
			if (current->token_type != NUMBER)
				SyntaxError("must be a Number");
			current_node = new TreeNode(ARRAY);
			current_node->left_child = new TreeNode(IDENTIFIER, identifier_name);
			current_node->right_child = new TreeNode(current);
			Match(NUMBER);
			Match(RBRACKET);
		}
		else
			current_node = new TreeNode(IDENTIFIER, identifier_name);
	}
	else if (current->token_type == LPAREN)
	{
		Match(LPAREN);
		if (current->token_type == IDENTIFIER)
		{
			DirectDeclarator(current_node);
			Match(IDENTIFIER);
		}
		Match(RPAREN);
	}
}

// parse the parameters and statements
void Parser::FunctionDeclaration(TreeNode* & current_node)
{
}
