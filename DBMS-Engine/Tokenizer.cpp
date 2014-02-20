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
 * Since \ is also used for escaping in C++, they have to be double-escaped:
 * E.g. ( is operator in regex, \( matches ( in regex, "\\(" matches ( in C++ regex
 */
const regex Tokenizer::OPERATORS = regex("(<-|<=|>=|>|<|!=|==|\\(|\\)|&&|\\|\\||,|;)");


vector<Token> Tokenizer::tokenize(const string& in)
{
    stringstream ss;
    // Find the operators and pad them with whitespace so they're easier tokenize
    ss << regex_replace(in, OPERATORS, " $1 ");

    vector<Token> tokens;
    string token;
    while(ss >> token)
        tokens.push_back(token);

    return tokens;
}

