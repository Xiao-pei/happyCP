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
			TreeNode* tmp = Declaration();
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
	TreeNodeKind default_kind = VARIABLE_DECLARATION;
	TreeNode* current_node = new TreeNode(VARIABLE_DECLARATION);
	switch (current->token_type)
	{
	case VOID:
		Match(VOID);
		base_type = VOID;
		current_node->token_type = IDENTIFIER;
		current_node->token_name = current->name;
		current_node->description = "Function declaration";
		current_node->kind = FUNCTION_DECLARATION;
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
	default:
		SyntaxError("unexpected type specifier");
	}
	if (current->token_type == SEMICOLON)
	{
		Match(SEMICOLON);
		current_node->description = "Empty declartion";
	}
	else if (current->token_type == LPAREN)
	{
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
			current_node->kind = FUNCTION_DECLARATION;
			current_node->left_child = new TreeNode(base_type);
			current_node->right_child = FunctionDeclaration();
		}
			//the left child holds variable type, and right child and its sibling holds declarators
		else
		{
			current_node->left_child = new TreeNode(base_type);
			current_node->description = "Variable declaration";
			current_node->right_child = new TreeNode(IDENTIFIER, token_name);
			if (current->token_type == COMMA)
				Match(COMMA);
			current_node->right_child->sibling = VariableDeclaratorList();
			if (current->token_type == SEMICOLON)
				Match(SEMICOLON);
			else
				SyntaxError("Expect ; behind a declaration");
		}
	}
	
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
		tmp->sibling = DirectDeclarator();
		tmp = tmp->sibling;
	}
	return current_node;
}

//parse IDENTIFIER|IDENTIFIER[NUMBER]|(direct_declarator) list
TreeNode* Parser::DirectDeclarator()
{
	TreeNode* current_node = nullptr;
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
TreeNode* Parser::FunctionDeclaration()
{
	Match(LPAREN);
	TreeNode* current_node = new TreeNode(FUNCTION_DECLARATION);
	if (current->token_type != RPAREN)
	{
		current_node->description = "parametes and statements";
		current_node->right_child = ParameterList();
	}
	Match(RPAREN);
	if (current->token_type == LBRACE)
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
	while (1)
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
		current_node->left_child = new TreeNode(base_type);
		current_node->right_child = new TreeNode(current);
		current_node->right_child->kind = ID_KIND;
		Match(IDENTIFIER);
		if (current->token_type == LBRACKET)
		{
			current_node->kind = ARRAY_PARAMETER;
			Match(LBRACKET);
			Match(RBRACKET);
		}
		else
			current_node->kind = PARAMETER;

		if (head_node == nullptr)
		{
			head_node = current_node;
			tmp = head_node;
		}
		else
		{
			tmp->sibling = current_node;
			tmp = current_node;
		}
		if (current->token_type == RPAREN)
			break;
		else
			Match(COMMA);
	}
	return head_node;
}

// parse the statements and local declarations
TreeNode* Parser::FunctionBody()
{
	TreeNode* head_node = nullptr;
	TreeNode* current_node = nullptr;
	while (current->token_type >= CHAR && current->token_type <= VOID)
	{
		if(!head_node)
		{
			head_node = Declaration();
			current_node = head_node;
		}
		else
		{
			current_node->sibling = Declaration();
			current_node = current_node->sibling;
		}
	}
	current_node->sibling = StatementList();
	return head_node;
}

TreeNode* Parser::StatementList()
{
	TreeNode* head_node = nullptr;
	TreeNode* current_node = nullptr;
	while (current->token_type != RBRACE)
	{
		current_node = Statement();
		if (head_node == nullptr)
			head_node = current_node;
		current_node = current_node->sibling;
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
	if (current->token_type == ELSE) //expression's sibling holds else statement 
	{
		head_node->description = "if-else statement";
		head_node->kind = IF_ELSE_STATEMENT;
		Match(ELSE);
		head_node->left_child->sibling = Statement();
	}
	return head_node;
}

TreeNode* Parser::IterationStatement()
{
	TreeNode* head_node = nullptr;
	if (current->token_type == WHILE)
	{
		head_node = new TreeNode(WHILE_STATEMENT);
		Match(WHILE);
		Match(LPAREN);
		head_node->left_child = Expression();
		Match(RPAREN);
		head_node->right_child = Statement();
	}
	else if (current->token_type == DO)
	{
		head_node = new TreeNode(DO_WHILE_STATEMENT);
		Match(DO);
		head_node->right_child = Statement();
		Match(WHILE);
		Match(LPAREN);
		head_node->left_child = Expression();
		Match(RPAREN);
	}
	else
	{
		head_node = new TreeNode(FOR_STATEMENT);
		Match(FOR);
		Match(LPAREN);
		head_node->left_child = Expression();
		Match(SEMICOLON);
		if (head_node->left_child)
		{
			head_node->left_child->sibling = Expression();
			Match(SEMICOLON);
			if (head_node->left_child->sibling)
				head_node->left_child->sibling->sibling = Expression();
		}
		else
			Match(SEMICOLON);	
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

TreeNode* Parser::Expression() // left child holds expressions seprated by comma
{
	if (current->token_type == SEMICOLON)
		return new TreeNode(EMPTY_EXPRESSION);
	TreeNode* head_node = AssigmentExpression();
	while (current->token_type == COMMA)
	{
		Match(COMMA);
		TreeNode* tmp = new TreeNode();
		if (tmp)
		{
			tmp->left_child = head_node;
			tmp->description = "comma seprated expression";
			tmp->right_child = AssigmentExpression();
			head_node = tmp;
		}
	}
	return head_node;
}

TreeNode* Parser::AssigmentExpression()
{
	TreeNode* head_node = nullptr;
	TreeNode* unary_node = UnaryExpression(); //may return nullptr
	if (current->token_type == ASSIGN)
	{
		if (unary_node != nullptr && unary_node->kind == UNARY_EXPRESSION)
		{
			Match(ASSIGN);
			head_node = new TreeNode(ASSIGNMENT_EXPRESSION);
			head_node->description = "Assign right node to left node";
			head_node->left_child = unary_node;
			head_node->right_child = AssigmentExpression();
		}
		else
		{
			SyntaxError("assigment error");
		}
	}
	else
	{
		head_node = LogicalOrExpression(unary_node);
	}
	return head_node;
}

TreeNode* Parser::LogicalOrExpression(TreeNode* passdown)
{
	TreeNode* head_node = nullptr;
	TreeNode* left_exp = LogicalAndExpression(passdown);
	while (current->token_type == LOGICALOR)
	{
		Match(LOGICALOR);
		head_node = new TreeNode(LOGICAL_OR_EXPRESSION);
		head_node->left_child = left_exp;
		head_node->right_child = LogicalAndExpression(nullptr);
		left_exp = head_node;
	}
	if (head_node)
		return head_node;
	else
		return left_exp;
}

TreeNode* Parser::LogicalAndExpression(TreeNode* passdown)
{
	TreeNode* head_node = nullptr;
	TreeNode* left_exp = InclusiveOrExpression(passdown);
	while (current->token_type == LOGICALAND)
	{
		Match(LOGICALAND);
		head_node = new TreeNode(LOGICAL_AND_EXPRESSION);
		head_node->left_child = left_exp;
		head_node->right_child = InclusiveOrExpression(nullptr);
		left_exp = head_node;
	}
	if (head_node)
		return head_node;
	else
		return left_exp;
}

TreeNode* Parser::InclusiveOrExpression(TreeNode* passdown)
{
	TreeNode* head_node = nullptr;
	TreeNode* left_exp = ExclusiveOrExpression(passdown);
	while (current->token_type == OR)
	{
		Match(OR);
		head_node = new TreeNode(INCLUSIVE_OR_EXPRESSION);
		head_node->left_child = left_exp;
		head_node->right_child = ExclusiveOrExpression(nullptr);
		left_exp = head_node;
	}
	if (head_node)
		return head_node;
	else
		return left_exp;
}

TreeNode* Parser::ExclusiveOrExpression(TreeNode* passdown)
{
	TreeNode* head_node = nullptr;
	TreeNode* left_exp = AndExpression(passdown);
	while (current->token_type == XOR)
	{
		Match(XOR);
		head_node = new TreeNode(LOGICAL_AND_EXPRESSION);
		head_node->left_child = left_exp;
		head_node->right_child = AndExpression(nullptr);
		left_exp = head_node;
	}
	if (head_node)
		return head_node;
	else
		return left_exp;
}

TreeNode* Parser::AndExpression(TreeNode* passdown)
{
	TreeNode* head_node = nullptr;
	TreeNode* left_exp = EqualityExpression(passdown);
	while (current->token_type == AND)
	{
		Match(AND);
		head_node = new TreeNode(AND_EXPRESSION);
		head_node->left_child = left_exp;
		head_node->right_child = EqualityExpression(nullptr);
		left_exp = head_node;
	}
	if (head_node)
		return head_node;
	else
		return left_exp;
}

TreeNode* Parser::EqualityExpression(TreeNode* passdown)
{
	TreeNode* head_node = nullptr;
	TreeNode* left_exp = RelationalExpression(passdown);
	while (true)
	{
		if (current->token_type == EQUAL)
		{
			head_node = new TreeNode(EQUALITY_EXPRESSION);
			Match(EQUAL);
			head_node->token_type = EQUAL;
		}
		else if (current->token_type == NOTEQUAL)
		{
			head_node = new TreeNode(EQUALITY_EXPRESSION);
			Match(NOTEQUAL);
			head_node->token_type = NOTEQUAL;
		}
		else
			break;
		head_node->left_child = left_exp;
		head_node->right_child = RelationalExpression(nullptr);
		left_exp = head_node;
	}
	if (head_node)
		return head_node;
	else
		return left_exp;
}

TreeNode* Parser::RelationalExpression(TreeNode* passdown)
{
	TreeNode* head_node = nullptr;
	TreeNode* left_exp = AdditiveExpression(passdown);
	while (true)
	{
		if (current->token_type == LESSTHAN)
		{
			head_node = new TreeNode(RELATIONAL_EXPRESSION);
			Match(LESSTHAN);
			head_node->token_type = LESSTHAN;
		}
		else if (current->token_type == GREATERTHAN)
		{
			head_node = new TreeNode(RELATIONAL_EXPRESSION);
			Match(GREATERTHAN);
			head_node->token_type = GREATERTHAN;
		}
		else
			break;
		head_node->left_child = left_exp;
		head_node->right_child = AdditiveExpression(nullptr);
		left_exp = head_node;
	}
	if (head_node)
		return head_node;
	else
		return left_exp;
}

TreeNode* Parser::AdditiveExpression(TreeNode* passdown)
{
	TreeNode* head_node = nullptr;
	TreeNode* left_exp = MultiplicativeExpression(passdown);
	while (true)
	{
		if (current->token_type == MIUNS)
		{
			head_node = new TreeNode(ADDITIVE_EXPRESSION);
			Match(MIUNS);
			head_node->token_type = MIUNS;
		}
		else if (current->token_type == PLUS)
		{
			head_node = new TreeNode(ADDITIVE_EXPRESSION);
			Match(PLUS);
			head_node->token_type = PLUS;
		}
		else
			break;
		head_node->left_child = left_exp;
		head_node->right_child = MultiplicativeExpression(nullptr);
		left_exp = head_node;
	}
	if (head_node)
		return head_node;
	else
		return left_exp;
}

TreeNode* Parser::MultiplicativeExpression(TreeNode* passdown)
{
	TreeNode* head_node = nullptr;
	TreeNode* left_exp = passdown;
	while (true)
	{
		if (current->token_type == TIMES)
		{
			head_node = new TreeNode(MULTIPLICATIVE_EXPRESSION);
			Match(TIMES);
			head_node->token_type = TIMES;
		}
		else if (current->token_type == DIVISION)
		{
			head_node = new TreeNode(MULTIPLICATIVE_EXPRESSION);
			Match(DIVISION);
			head_node->token_type = DIVISION;
		}
		else
			break;
		head_node->left_child = left_exp;
		head_node->right_child = UnaryExpression();
		left_exp = head_node;
	}
	if (head_node)
		return head_node;
	else
		return left_exp;
}

TreeNode* Parser::UnaryExpression()
{
	TreeNode* head_node = nullptr;
	if (current->token_type == INCREMENT)
	{
		Match(INCREMENT);
		head_node = new TreeNode(UNARY_EXPRESSION);
		head_node->token_type = INCREMENT;
		head_node->right_child = UnaryExpression();
	}
	else if (current->token_type == DECREMENT)
	{
		Match(DECREMENT);
		head_node = new TreeNode(UNARY_EXPRESSION);
		head_node->token_type = DECREMENT;
		head_node->right_child = UnaryExpression();
	}
	else if (current->token_type == IDENTIFIER)
	{
		head_node = new TreeNode(UNARY_EXPRESSION);
		head_node->left_child = new TreeNode(current);
		Match(IDENTIFIER);
		head_node->right_child = PostfixExpression();
	}
	else if (current->token_type == LPAREN)
	{
		Match(LPAREN);
		head_node = new TreeNode(UNARY_EXPRESSION);
		head_node->left_child = Expression();
		head_node->right_child = PostfixExpression();
		Match(RPAREN);
	}
	else
	{
		SyntaxError("expression error");
	}
	return head_node;
}

TreeNode* Parser::PostfixExpression()
{
	TreeNode* head_node = nullptr;
	TreeNode* tmp = nullptr;
	while (true)
	{
		if (current->token_type == LPAREN)
		{
			tmp = new TreeNode(FUNCTION_CALL);
			Match(LPAREN);
			if (current->token_type == RPAREN)
				Match(RPAREN);
			else
			{
				tmp->left_child = Expression();
			}
		}
		else if (current->token_type == PERIOD)
		{
			tmp = new TreeNode(ELEMENT_ACCESS);
			Match(PERIOD);
			if (current->token_type == IDENTIFIER)
			{
				tmp->left_child = new TreeNode(current);
				Match(IDENTIFIER);
			}
			else
			{
				SyntaxError("Must be access an ID ");
			}
		}
		else if (current->token_type == INCREMENT || current->token_type == DECREMENT)
		{
			tmp = new TreeNode(current);
			tmp->kind = SELF_INC_OR_DEC;
			Match(current->token_type);
		}
		else if (current->token_type == LBRACKET)
		{
			Match(LBRACKET);
			tmp = new TreeNode(ARRAY_ACCESS);
			tmp->left_child = Expression();
			Match(RBRACKET);
		}
		else
		{
			break;
		}
		if (!head_node)
			head_node = tmp;
		tmp = tmp->right_child;
	}
	return head_node;
}
