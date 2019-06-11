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
		return std::to_string(line_num) +": Type: \x1b[31m" + TokenTypeNames[token_type] + "\x1b[0m Name: " + name;
	return  std::to_string(line_num)  +": Type: \x1b[32m" + TokenTypeNames[token_type] + "\x1b[0m Name: \x1b[36m" + name + "\x1b[0m";
}

Token::~Token()
{
}
