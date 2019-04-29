#ifndef __LEXICAL_H__
#define __LEXICAL_H__
#include"StateMachine.h"

class Lexical //the main program, Lexical Analyzer
{
private:
	string filename;
	StateMachine* state_machine;
public:
	Lexical();
	~Lexical();
	void set_filename(string);
	Token* get_token();
};

#endif
