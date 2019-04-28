#ifndef __TOKEN_H__
#define __TOKEN_H__
#include "stuff.h"

class Token
{
public:
	TokenType token_type;
	string name;
	int line_num;
	Token(TokenType t, string n);
	Token(TokenType t, string n, int l);
	~Token();
	string to_string();
};

#endif
