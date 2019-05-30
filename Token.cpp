#include "Token.h"


Token::Token(TokenType t, string n)
{
	token_type = t;
	name = n;
}

Token::Token(TokenType t, string n, int l)
{
	token_type = t;
	name = n;
	line_num = l;
}

string Token::to_string()
{
	if (token_type == ERROR)
		return "Type: \x1b[31m" + TokenTypeNames[token_type] + "\033[0m Name: " + name;
	return "Type: \033[22;36m" + TokenTypeNames[token_type] + "\033[0m Name: \x1b[36m" + name+ "\033[0m";
}

Token::~Token()
{
}
