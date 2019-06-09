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
	TreeNode* Declaration();
	//void VariableDeclaration();
	TreeNode* VariableDeclaratorList();
	TreeNode* DirectDeclarator();
	TreeNode* FunctionDeclaration();
	TreeNode* ParameterList();
	TreeNode* FunctionBody();
	TreeNode* Statement();
	TreeNode* StatementList();
	TreeNode* IfStatement();
	TreeNode* IterationStatement();
	TreeNode* JumpStatement();
	TreeNode* ExpressionStatement();
	TreeNode* CompoundStatement();
	TreeNode* Expression();
	TreeNode* AssigmentExpression();
	TreeNode* LogicalOrExpression(TreeNode*);
	TreeNode* UnaryExpression();
	TreeNode* LogicalAndExpression(TreeNode*);
	TreeNode* InclusiveOrExpression(TreeNode*);
	TreeNode* ExclusiveOrExpression(TreeNode*);
	TreeNode* AndExpression(TreeNode*);
	TreeNode* EqualityExpression(TreeNode*);
	TreeNode* RelationalExpression(TreeNode*);
	TreeNode* AdditiveExpression(TreeNode*);
	TreeNode* MultiplicativeExpression(TreeNode*);
	TreeNode* PostfixExpression();
public:
	Parser(Lexical*);
	void Parse();
	TreeNode* getRoot() { return root_node; }
};

#endif
