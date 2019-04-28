#ifndef __STATES_H__
#define __STATES_H__
#include "stuff.h"
#include "StateMachine.h"


class BeginStates : public BaseState
{
public:
	BeginStates();
	BaseState* GetNextState(char c) override;
	bool isEndState() override { return false; }
};

class IDStates : public BaseState
{
public:
	IDStates(string);
	BaseState* GetNextState(char c) override;
	bool isEndState() override { return false; }
};

class NUMStates : public BaseState //NUMBER
{
public:
	NUMStates(string);
	BaseState* GetNextState(char c) override;
	bool isEndState() override { return false; }
};

class ENDStates : public BaseState
{
public:
	ENDStates(string, TokenType);
	BaseState* GetNextState(char c) override;
	bool isEndState() override { return true; }
};

class SymbolsStates : public BaseState
{
public:
	SymbolsStates(string s) { name = s; }
	BaseState* GetNextState(char c) override;
	bool isEndState() override { return false; }
};

class CommentStates : public BaseState
{
public:
	CommentStates(string s) { name = s; }
	BaseState* GetNextState(char c) override;
	bool isEndState() override { return false; }
};

class SciNUMStates : public BaseState //Scientific counting
{
public:
	SciNUMStates(string s) { name = s; }
	BaseState* GetNextState(char c) override;
	bool isEndState() override { return false; }
};

class INTStates : public BaseState //Scientific counting
{
public:
	INTStates(string s)
	{
		name = s;
		token_type = NUMBER;
	}
	BaseState* GetNextState(char c) override;
	bool isEndState() override { return false; }
};
#endif
