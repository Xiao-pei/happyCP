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

	TreeNode(): left_child(nullptr), right_child(nullptr), sibling(nullptr),token_type(EMPTY)
	{
	}

	TreeNode(TreeNodeKind k): left_child(nullptr), right_child(nullptr),
	                          sibling(nullptr), kind(k),token_type(EMPTY)
	{
	}

	TreeNode(Token* t): left_child(nullptr), right_child(nullptr),
	                    sibling(nullptr), token_type(t->token_type), token_name(t->name)
	{
		if(token_type == IDENTIFIER)
			kind = ID_KIND;
		if(token_type == NUMBER || token_type == TRUE || token_type == FALSE)
			kind = CONSTANT;
	}

	TreeNode(TokenType t): left_child(nullptr), right_child(nullptr),
	                       sibling(nullptr), token_type(t)
	{
		if (token_type>=CHAR && token_type<=VOID)
			kind = TYPE_SPECIFIER;
	}

	TreeNode(TokenType t, string n): left_child(nullptr), right_child(nullptr),
	                                 sibling(nullptr), token_name(n), token_type(t)
	{
		if(token_type == IDENTIFIER)
			kind = ID_KIND;
	}
};
#endif
