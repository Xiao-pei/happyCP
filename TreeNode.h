#ifndef __TREENODE_H__
#define __TREENODE_H__
#include "Token.h"


class TreeNode
{
public:
	TreeNode* left_child;
	TreeNode* right_child;
	TreeNode* sibling;
	TokenType token_type;
	string token_name;
	string description;
	TreeNodeKind kind;
	TreeNode(): left_child(nullptr), right_child(nullptr), sibling(nullptr){}

	TreeNode(TreeNodeKind k): left_child(nullptr), right_child(nullptr), 
		sibling(nullptr), kind(k){}

	TreeNode(Token* t): left_child(nullptr), right_child(nullptr), 
		sibling(nullptr),token_type(t->token_type),token_name(t->name){}

	TreeNode(TokenType t): left_child(nullptr), right_child(nullptr), 
		sibling(nullptr), token_type(t){}

	TreeNode(TokenType t, string n): left_child(nullptr), right_child(nullptr), 
		sibling(nullptr), token_name(n), token_type(t){}
};
#endif
