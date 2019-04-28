#include "StateMachine.h"
#include <cstdarg>


StateMachine::StateMachine()
{
	current_state = new BeginStates();
	line_num = 0;
	end = false;
}

StateMachine::StateMachine(string s)
{
	ifs.open(s);
	current_state = new BeginStates();
	line_num = 0;
	end = false;
}


StateMachine::~StateMachine()
{
	if (current_state)
		delete current_state;
}

bool StateMachine::isEndState()
{
	return end;
}

void StateMachine::ChangeState()
{
	char c;
	if (ifs.is_open())
		ifs.get(c);
	else
		cin.get(c);
	if (c == '\n')
		++line_num;
	BaseState* tmp = current_state;
	current_state = current_state->GetNextState(c);
	if (tmp->needPutback())
	{
		if (ifs.is_open())
			ifs.putback(c);
		else
			cin.putback(c);
		if (c == '\n')
			--line_num;
	}
	end = current_state->isEndState();
	delete tmp;
}


Token* StateMachine::get_token()
{
	Token* token = current_state->GetToken();
	token->line_num = line_num;
	return token;
}

void StateMachine::reset()
{
	end = false;
	if (current_state)
		delete current_state;
	current_state = new BeginStates();
}
