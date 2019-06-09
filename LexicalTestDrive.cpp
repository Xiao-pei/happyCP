#include "stuff.h"
#include "Lexical.h"
#include "Parser.h"

void printSpace(int count)
{
	while (count--)
	{
		cout<<"  ";
	}
}

void printTree(TreeNode* root,int depth)
{
	if(root->left_child)
	{
		//cout<<"L: ";
		printTree(root->left_child,depth+1);
	}
	printSpace(depth);
	cout<<"kind:  \x1b[31m"<<TokenTypeNames[root->kind]<<"\033[0m ID name: "<<root->token_name<<" token type: "<<TokenTypeNames[root->token_type]<<endl;
	if(root->right_child)
	{
		//cout<<"R: ";
		printTree(root->right_child,depth+1);
	}
	if(root->sibling)
	{
		//cout<<"S: ";
		printTree(root->sibling,depth);
	}
}


int main(int argc, char* argv[])
{
	Lexical* lexical = new Lexical();
	if (argc == 2)
	{
		lexical->set_filename(argv[1]);
	}
	Parser* parser = new Parser(lexical);
	parser->Parse();
	TreeNode* node = parser->getRoot();
	cout << node->description << endl;
	printTree(node,0);
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
