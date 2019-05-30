#include "Lexical.h"


Lexical::Lexical()
{
	state_machine = nullptr;
}

Lexical::~Lexical()
{
	if (state_machine)
		delete state_machine;
}

void Lexical::set_filename(string s)
{
	filename = s;
	state_machine = new StateMachine(s);
}


Token* Lexical::get_token()
{
	if (!state_machine)
		state_machine = new StateMachine();
	while (!state_machine->isEndState())
		state_machine->ChangeState();
	Token* result = state_machine->get_token();
	state_machine->reset();
	return result;
}
