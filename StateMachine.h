#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__
#include "stuff.h"
#include "BaseState.h"
#include "Token.h"
#include "States.h"

class StateMachine
{
private:
	BaseState* current_state;
	int line_num;
	bool end;
	ifstream ifs;
public:
	StateMachine();
	StateMachine(string);
	~StateMachine();
	bool isEndState();
	void ChangeState();
	Token* get_token();
	void reset();
};

#endif
