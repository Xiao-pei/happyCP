#include "stuff.h"
#include "Lexical.h"
#include "Parser.h"

int main(int argc, char *argv[])
{
	Lexical *lexical = new Lexical();
	if (argc == 2)
	{
		lexical->set_filename(argv[1]);
	}
	Parser *parser = new Parser(lexical);
	parser->Parse();
	TreeNode* node = parser->getRoot();
	cout << node->description<<endl;
	// Token *token = lexical->get_token();
	// while (true)
	// {
	// 	if (token->token_type == ENDOFFILE)
	// 		break;
	// 	cout << "line number: " << token->line_num << " ;" << token->to_string() << "   " << endl;
	// 	token = lexical->get_token();
	// }
	return 0;
}
