#ifndef __PARSER_H__
#define __PARSER_H__
#include "Lexical.h"
#include "TreeNode.h"

class Parser
{
private:
	Lexical* lexial;
	Token* current;
	TreeNode* root_node;

	void Program();
	void SyntaxError(string);
	void Match(TokenType);
	void DeclarationList();
	void Declaration(TreeNode*&);
	//void VariableDeclaration();
	void VariableDeclaratorList(TreeNode*&);
	void DirectDeclarator(TreeNode*&);
	void FunctionDeclaration(TreeNode*&);
	void Statement();
	void StatementList();
public:
	Parser(Lexical*);
	void Parse();
	TreeNode* getRoot() { return root_node; }
};

#endif
