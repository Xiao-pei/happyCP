#include "stuff.h"
#include "Lexical.h"
#include "Parser.h"

void printSpace(int count)
{
	while (count--)
	{
		cout<<"\x1b[100m |\x1b[40m";
	}
}

void printTree(TreeNode* root,int depth)
{
	if(root->left_child)
	{
		cout<<"\x1b[33m";
		printTree(root->left_child,depth+1);
		//cout<<"\033[0m";
	}
	printSpace(depth);
	if(root->token_name.length()>=1)
		cout<<"Kind: \x1b[36m"<<TokenTypeNames[root->kind]<<"\033[0m ID name: "<<root->token_name<<"  Token type: "<<TokenTypeNames[root->token_type]<<"\033[0m"<<endl;
	else
		cout<<"Kind: \x1b[36m"<<TokenTypeNames[root->kind]<<"\033[0m  Token type: "<<TokenTypeNames[root->token_type]<<"\033[0m"<<endl;
	if(root->right_child)
	{
		//cout<<"\x1b[36m";
		printTree(root->right_child,depth+1);
		//cout<<"\033[0m";
	}
	if(root->sibling)
	{
		//cout<<"\x1b[36m";
		printTree(root->sibling,depth);
		//cout<<"\033[0m";
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
