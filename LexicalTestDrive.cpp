#include "stuff.h"
#include "Lexical.h"
int main(int argc, char* argv[])
{
	Lexical* lexical = new Lexical();
	if (argc == 2)
	{
		lexical->set_filename(argv[1]);
	}
	Token* token = lexical->get_token();
	while (true)
	{
		if (token->token_type == ENDOFFILE)
			break;
		cout << "line number: "  << token->line_num << " ;" << token->to_string() << "   " << endl;
		token = lexical->get_token();
	}
	return 0;

}
