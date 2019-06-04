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
	root_node = Declaration();
	TreeNode* current_node = root_node;
	while (current->token_type != ENDOFFILE && current->token_type != ELSE)
	{
		if (root_node != nullptr)
		{
			TreeNode* tmp= Declaration();
			current_node->sibling = tmp;
			current_node = tmp;
		}
		else
			root_node = Declaration();
	}
}

TreeNode* Parser::Declaration()
{
	TokenType base_type = ERROR;
	TreeNodeKind default_kind = VARIABLE_DECLARTION;
	TreeNode* current_node = new TreeNode();
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
		current_node->right_child = FunctionDeclaration();
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
	case ENUM:
		Match(ENUM);
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
		current_node->left_child = new TreeNode(base_type);
		current_node->right_child = VariableDeclaratorList();
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
			current_node->right_child = FunctionDeclaration();
		}
	//the left child holds variable type, and right child and its sibling holds declarators
		else 
		{
			current_node->kind = VARIABLE_DECLARTION;
			current_node->left_child = new TreeNode(base_type);
			current_node->description = "Variable declaration";
			current_node->right_child = new TreeNode(IDENTIFIER, token_name);
			if(current->token_type==COMMA)
				Match(COMMA);
			current_node->right_child->sibling = VariableDeclaratorList();
		}
	}
	if (current->token_type == SEMICOLON)
		Match(SEMICOLON);
	else
		SyntaxError("Expect ; behind a declaration");
	return current_node;
}

//variable_declarator_list, direct_declarator| direct_declarator
TreeNode* Parser::VariableDeclaratorList()
{
	TreeNode* current_node;
	current_node = DirectDeclarator();
	TreeNode* tmp = current_node;
	while (current->token_type == COMMA)
	{
		Match(COMMA);
		tmp ->sibling = DirectDeclarator();
		tmp = tmp -> sibling;
	}
	return current_node;
}

//parse IDENTIFIER|IDENTIFIER[NUMBER]|(direct_declarator) list
TreeNode* Parser::DirectDeclarator()
{
	TreeNode* current_node;
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
			current_node = DirectDeclarator();
			Match(IDENTIFIER);
		}
		Match(RPAREN);
	}
	return current_node;
}

// parse the parameters and statements, the right node holds the parameters
// and the left node holds the statemsnts
TreeNode* Parser::FunctionDeclaration( )
{
	Match(LPAREN);
	TreeNode* current_node = new TreeNode();
	current_node->description = "parametes and statements";
	current_node->right_child =	ParameterList();
	Match(RPAREN);
	if(current->token_type == LBRACE)
	{
		current_node->left_child = CompoundStatement();
	}
	else
		Match(SEMICOLON);
	return current_node;
}

TreeNode* Parser::ParameterList()
{
	TreeNode* head_node = nullptr;
	TreeNode* tmp = nullptr;
	while(1)
	{
		TokenType base_type = ERROR;
		TreeNode* current_node = new TreeNode();
		switch (current->token_type)
		{
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
		default:
			SyntaxError("Unexpected type specifier");
		} 
		current_node ->left_child = new TreeNode(base_type);
		current_node ->right_child = new TreeNode(current);
		Match(IDENTIFIER);
		if(current->token_type == LBRACKET)
		{
			current_node->kind = ARRAY_PARAMETER;
			Match(LBRACKET);
			Match(RBRACKET);
		}
		else
			current_node->kind = PARAMETER;
		if(head_node == nullptr){
			head_node = current_node;
			tmp = head_node;
		}
		else
		{
			tmp->sibling = current_node;
			tmp = current_node;
		}
		if(current->token_type == RPAREN)
			break;
		else
			Match(COMMA);
	}
	return head_node;
}

// parse the statements and local declartions
TreeNode* Parser::FunctionBody() 
{
	TreeNode* head_node = nullptr;
	TreeNode* current_node;
	bool first = true;
	while(current->token_type >= INT && current->token_type <= VOID)
	{
		current_node = Declaration();
		if(head_node == nullptr)
			head_node = current_node;
		current_node = current_node ->sibling;
	}
	current_node = StatementList();
	return current_node;
}

TreeNode* Parser::StatementList()
{
	TreeNode* head_node = nullptr;
	TreeNode* current_node;
	while(current->token_type!=RBRACE)
	{
		current_node = Statement();
		if(head_node == nullptr)
			head_node = current_node;
		current_node=current_node->sibling;
	}
	return head_node;
}

TreeNode* Parser::CompoundStatement()
{
	Match(LBRACE);
	TreeNode* node = FunctionBody();
	Match(RBRACE);
	return node;
}

TreeNode* Parser::Statement()
{
	TreeNode* head_node = nullptr;
	switch (current->token_type)
	{
	case IF:
		head_node = IfStatement();
		break;
	case WHILE:
	case DO:
	case FOR:
		head_node = IterationStatement();
		break;
	case BREAK:
	case RETURN:
	case CONTINUE:
		head_node = JumpStatement();
		break;
	case IDENTIFIER:
		head_node = ExpressionStatement();
	case LBRACE:
		head_node = CompoundStatement();
	default:
		SyntaxError("unexpected token");
		break;
	}

	return head_node;
}

TreeNode* Parser::IfStatement()
{
	TreeNode* head_node = new TreeNode(IF_STATEMENT);
	head_node->description = "if statement";
	Match(IF);
	Match(LPAREN);
	head_node->left_child = Expression();
	Match(RPAREN);
	head_node->right_child = Statement();
	if(current->token_type == ELSE) //expression's sibling holds else statement 
	{
		head_node->description = "if-else statement";
		head_node->kind = IF_ELSE_STATEMENT;
		Match(ELSE);
		head_node->left_child->sibling = Statement();
	}
	return head_node;
}

TreeNode* Parser::IterationStatement(){
	TreeNode* head_node = nullptr;
	if(current->token_type == WHILE)
	{
		Match(WHILE);
		Match(LPAREN);
		head_node ->left_child = Expression();
		Match(RPAREN);
		head_node->right_child = Statement();
	}
	else if (current->token_type == DO)
	{
		Match(DO);
		head_node -> right_child = Statement();
		Match(WHILE);
		Match(LPAREN);
		head_node -> left_child = Expression();
		Match(RPAREN);
	}
	else
	{
		Match(FOR);
		Match(LPAREN);
		head_node->left_child = Expression();
		Match(SEMICOLON);
		if(head_node->left_child)
			head_node ->left_child ->sibling = Expression();
		Match(SEMICOLON);
		if(head_node->left_child->sibling)
			head_node->left_child->sibling->sibling = Expression();
		Match(RPAREN);
		head_node->right_child = Statement();
	}
	return head_node;	
}

TreeNode* Parser::JumpStatement()
{
	TreeNode* head_node = new TreeNode();
	switch (current->token_type)
	{
	case BREAK:
		Match(BREAK);
		head_node->kind = BREAK_STATEMENT;
		head_node->description = "break statement";
		Match(SEMICOLON);
		break;
	case CONTINUE:
		Match(CONTINUE);
		head_node->kind = CONTINUE_STATEMENT;
		head_node->description = "continue statement";
		Match(SEMICOLON);
		break;
	case RETURN:
		Match(RETURN);
		head_node->kind = RETURN_STATEMENT;
		head_node->description = "return statement";
		if (current->token_type != SEMICOLON)
		{
			head_node->left_child = Expression();
		}
		Match(SEMICOLON);
	default:
		SyntaxError("unexpected token");
		break;
	}
	return head_node;
}

TreeNode* Parser::ExpressionStatement()
{
	TreeNode* head_node = Expression();
	Match(SEMICOLON);
	return head_node;
}

TreeNode* Parser::Expression()
{
	if(current->token_type == SEMICOLON)
		return new TreeNode(EMPTY_EXPRESSION);
	
	// TODO
}