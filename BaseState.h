#ifndef __BASESTATE_H__
#define __BASESTATE_H__
#include "stuff.h"
#include "Token.h"

class BaseState
{
protected:
	string name;
	TokenType token_type;
	bool putback = false;
public:
	virtual ~BaseState() = default;
	virtual BaseState* GetNextState(char c) = 0;
	virtual Token* GetToken() { return new Token(token_type, name); }
	virtual bool isEndState() = 0;
	virtual bool needPutback() { return putback; }
	string getName() { return name; }
};
#endif
