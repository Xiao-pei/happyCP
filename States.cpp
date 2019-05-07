#include "States.h"


BeginStates::BeginStates()
{
	name = "";
}

BaseState* BeginStates::GetNextState(char c)
{
	BaseState* nexstate;
	if (c == EOF)
	{
		nexstate = new ENDStates("EOF", ENDOFFILE);
	}
	else if (isalpha(c))
	{
		name = c;
		nexstate = new IDStates(name);
	}
	else if (isdigit(c))
	{
		name = c;
		nexstate = new NUMStates(name);
	}
	else if (isSymbols(c))
	{
		switch (c)
		{
		case '=':
			return new SymbolsStates("=");
		case '/':
			return new SymbolsStates("/");
		case '+':
			return new SymbolsStates("+");
		case '-':
			return new SymbolsStates("-");
		case '<':
			return new ENDStates("<", LESSTHAN);
		case '&':
			return new SymbolsStates("&");
		case '|':
			return new SymbolsStates("|");
		case '!':
			return new SymbolsStates("!");
		case '^':
			return new ENDStates("^", XOR);
		case '~':
			return new ENDStates("~", NOT);
		case '*':
			return new ENDStates("*", TIMES);
		case '>':
			return new ENDStates(">", GREATERTHAN);
		case '(':
			return new ENDStates("(", LPAREN);
		case ')':
			return new ENDStates(")", RPAREN);
		case ';':
			return new ENDStates(";", SEMICOLON);
		case '{':
			return new ENDStates("{", LBRACE);
		case '}':
			return new ENDStates("}", RBRACE);
		case ',':
			return new ENDStates(",", COMMA);
		case '[':
			return new ENDStates("[", LBRACKET);
		case ']':
			return new ENDStates("]", RBRACKET);
		default:
			name += c;
			return new ENDStates(name, ERROR);
		}
	}
	else { nexstate = new BeginStates(); }
	return nexstate;
}


IDStates::IDStates(string s)
{
	name = s;
	token_type = IDENTIFIER;
}

BaseState* IDStates::GetNextState(char c)
{
	if (isOthers(c))
	{
		putback = true;
		return new ENDStates(name, IDENTIFIER);
	}
	else
	{
		name += c;
		if (RWordsMap[name])
		{
			return new ENDStates(name, RWordsMap[name]);
		}
		return new IDStates(name);
	}
}

NUMStates::NUMStates(string s)
{
	name = s;
	token_type = NUMBER;
}

BaseState* NUMStates::GetNextState(char c)
{
	if (c == '.')
	{
		if (name.length() == 1)
		{
			name += c;
			return new SciNUMStates(name);
		}
		else
		{
			name += c;
			return new INTStates(name);
		}
	}
	else if (isdigit(c))
	{
		name += c;
		return new NUMStates(name);
	}
	else if (isalpha(c))
	{
		name += c;
		return new ENDStates(name, ERROR);
	}
	else
	{
		putback = true;
		return new ENDStates(name, token_type);
	}
}


ENDStates::ENDStates(string s, TokenType t)
{
	name = s;
	token_type = t;
}

BaseState* ENDStates::GetNextState(char c)
{
	return new ENDStates(name, token_type);
}

BaseState* SymbolsStates::GetNextState(char c)
{
	if (name == "=")
	{
		if (c == '=')
			return new ENDStates("==", EQUAL);

		putback = true;
		return new ENDStates("=", ASSIGN);
	}
	if (name == "/")
	{
		if (c == '*')
			return new CommentStates("*");
		else if (c == '/')
			return new CommentStates("\n");
		else
		{
			putback = true;
			return new ENDStates("/", DIVISION);
		}
	}
	if (name == "&")
	{
		if (c == '&')
			return new ENDStates("&&", LOGICALAND);

		putback = true;
		return new ENDStates("&", AND);
	}
	if (name == "|")
	{
		if (c == '|')
			return new ENDStates("||", LOGICALOR);

		putback = true;
		return new ENDStates("|", OR);
	}
	if (name == "!")
	{
		if (c == '=')
			return new ENDStates("!=", NOTEQUAL);

		putback = true;
		return new ENDStates("!", LOGICALNOT);

	}
	if(name == "+")
	{
		if (c == '+')
			return new ENDStates("++", INCREMENT);

		putback = true;
		return new ENDStates("+", PLUS);
	}
	if (name == "-")
	{
		if (c == '-')
			return new ENDStates("--", DECREMENT);

		putback = true;
		return new ENDStates("-", MIUNS);
	}
	return new ENDStates(name, ERROR);
}


BaseState* CommentStates::GetNextState(char c)
{
	if (c == name[0])
	{
		switch (c)
		{
		case '*': return new CommentStates("/");
		case '/': return new BeginStates();
		case '\n': return new BeginStates();
		default: return new ENDStates("COMMENT", ERROR);
		}
	}
	else return new CommentStates(name);
}

BaseState* SciNUMStates::GetNextState(char c)
{
	if (isdigit(c))
	{
		name += c;
		return new SciNUMStates(name);
	}
	if (c == 'e' || c == 'E')
	{
		name += c;
		return new SciNUMStates(name);
	}
	if (c == '+' || c == '-')
	{
		if (name[name.length() - 1] == 'e' || name[name.length() - 1] == 'E')
		{
			name += c;
			return new INTStates(name);
		}
		return new ENDStates(name, ERROR);
	}
	if (isOthers(c))
	{
		putback = true;
		return new ENDStates(name, NUMBER);
	}
	name += c;
	return new ENDStates(name, ERROR);
}

BaseState* INTStates::GetNextState(char c)
{
	if (isdigit(c))
	{
		name += c;
		return new INTStates(name);
	}
	else if (isalpha(c))
	{
		name += c;
		return new ENDStates(name, ERROR);
	}
	else
	{
		putback = true;
		return new ENDStates(name, token_type);
	}
}
