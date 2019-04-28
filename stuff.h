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
	LPAREN,
	RPAREN,
	SEMICOLON,
	LBRACE,
	RBRACE,
	COMMA,
	DIVISION,
	INCREMENT,
	DECREMENT,
	ERROR,
	ENDOFFILE
};

static string TokenTypeNames[40] = {
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
	"ERROR"
};
static map<string, TokenType> RWordsMap = {
	{"if",IF},{"else",ELSE},{"while",WHILE},{"do",DO},{"char",CHAR},
	{"int",INT},{"float",FLOAT},{"double",DOUBLE},{"bool",BOOL},{"void",VOID},
	{"true",TRUE},{"false",FALSE},{"for",FOR}
};

bool static isOthers(char c)
{
	return !isdigit(c) && !isalpha(c);
}

bool static isSymbols(char c)
{
	return (c > ' ' && c < '0') || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || c == '{' || c == '}' || c == '|';
}
#endif
