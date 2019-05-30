#ifndef __STUFF_H__
#define __STUFF_H__
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#define MAXLINELENGTH 128
using namespace std;

enum TokenType
{
	IDENTIFIER,
	NUMBER,
	/* reserved words */
	IF,
	ELSE,
	WHILE,
	FOR,
	DO,
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	BOOL,
	VOID,
	TRUE,
	FALSE,
	BREAK,
	RETURN,
	CONST,
	ENUM,
	/* special symbols */
	ASSIGN,
	EQUAL,
	NOTEQUAL,
	PLUS,
	MIUNS,
	LESSTHAN,
	AND,
	OR,
	XOR,
	NOT,
	LOGICALAND,
	LOGICALOR,
	LOGICALNOT,
	TIMES,
	GREATERTHAN,
	// "("
	LPAREN,
	RPAREN,
	SEMICOLON,
	// "{"
	LBRACE,
	RBRACE,
	COMMA,
	DIVISION,
	INCREMENT,
	DECREMENT,
	//"["
	LBRACKET,
	RBRACKET,
	ERROR,
	ENDOFFILE
};

enum TreeNodeKind
{
	VARIABLE_DECLARTION = ENDOFFILE+1,
	FUNCTION_DECLARTION,
	ARRAY

};

static string TokenTypeNames[46] = {
	"IDENTIFIER",
	"NUMBER",
	"IF",
	"ELSE",
	"WHILE",
	"FOR",
	"DO",
	"CHAR",
	"INT",
	"FLOAT",
	"DOUBLE",
	"BOOL",
	"VOID",
	"TRUE",
	"FALSE",
	"BREAK",
	"RETURN",
	"CONST",
	"ENUM",
	// symbols
	"ASSIGN",
	"EQUAL",
	"NOTEQUAL",
	"PLUS",
	"MIUNS",
	"LESSTHAN",
	"AND",
	"OR",
	"XOR",
	"NOT",
	"LOGICALAND",
	"LOGICALOR",
	"LOGICALNOT",
	"TIMES",
	"GREATERTHAN",
	"LPAREN",
	"RPAREN",
	"SEMICOLON",
	"LBRACE",
	"RBRACE",
	"COMMA",
	"DIVISION",
	"INCREMENT",
	"DECREMENT",
	"LBRACKET", //"["
	"RBRACKET",
	"ERROR"
};
static map<string, TokenType> RWordsMap = {
	{"if", IF}, {"else", ELSE}, {"while", WHILE}, {"do", DO}, {"char", CHAR}, {"const", CONST},
	{"int", INT}, {"float", FLOAT}, {"double", DOUBLE}, {"bool", BOOL}, {"void", VOID},{"enum",ENUM},
	{"true", TRUE}, {"false", FALSE}, {"for", FOR}, {"break", BREAK}, {"return", RETURN}
}; // add reserved words into ths list

bool static isOthers(char c)
{
	char a = L'2';
	return !isdigit(c) && !isalpha(c);
}

bool static isSymbols(char c)
{
	return (c > ' ' && c < '0') || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || c == '{' || c == '}' || c == '|';
}
#endif
