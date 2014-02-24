/*
* Tokenizer.cpp
*
*  Created on: Feb 16, 2014
*      Author: Synix
*/

#include "Tokenizer.h"

#include <sstream>


/* This is a list of operators separated by regex alternation operator |
* Some characters are used in regex patterns themselves, so they have to be escaped
* Since \ is also used for escaping in C++, the R prefix disables C++ escaping:
* E.g. ( is operator in regex, \( matches ( in regex, R"(\()" matches ( in C++ regex
*/
const regex Tokenizer::OPERATORS
= regex(R"((\\"|\"|<-|<=|>=|>|<|!=|==|\(|\)|&&|\|\||,|;))");

const regex Tokenizer::SPACED_OPERATORS
= regex(R"( (\\"|\"|<-|<=|>=|>|<|!=|==|\(|\)|&&|\|\||,|;) )");


vector<Token> Tokenizer::tokenize(const string& in)
{
	stringstream ss;
	// Find the operators and pad them with whitespace so they're easier tokenize
	ss << regex_replace(in, OPERATORS, " $1 ");

	vector<Token> tokens;
	string token;
	while (ss >> token)
	{
		if (token == "\"") // Matching literal strings: too complicated to explain here :P
		{
			token = ' ' + token;
			char prev = 0, next;
			while ((next = ss.get()) != EOF)
			{
				token += next;
				if (prev != '\\' && next == '"')
					break;

				prev = next;
			}
			token += ' ';
			token = regex_replace(token, SPACED_OPERATORS, "$1");
		}
		tokens.push_back(token);
	}

	return tokens;
}

bool isQuoted(const string& str)
{
	return (str[0] == '"' && str.back() == '"');
}

bool isAlnum(const string& str)
{
	return regex_match(str, regex(R"([a-zA-Z_]\w*)"));
}

// This function assumes that the input is quoted
// It doesn't modify the object
string removeQuotes(const string& str)
{
	return str.substr(1, str.length() - 2);
}

int stringToInt(const string& str)
{
	size_t i;
	int result = stoi(str, &i);
	if (str.substr(i) != "")
		throw "'stringToInt' failed.";
	return result;

}
