/*
 * Tokenizer.h
 *
 *  Created on: Feb 16, 2014
 *      Author: Synix
 */

#pragma once

#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <locale>

using std::regex;
using std::string;
using std::vector;

// Basically a string without unwanted content
struct Token
{
    string str;

	Token() {};
    Token(string token) : str(token) {}
    Token(const char* token) : str(token) {}

    operator string&() { return str; }
    bool operator==(const string& s) { return str == s; }
    bool operator!=(const string& s) { return !((*this) == s); }

};


// Functions that help tokenize the input
class Tokenizer
{
    // Order matters! E.g. if ">" matches first, then ">=" will never find a match [REGEX]
    static const regex OPERATORS;
    static const regex SPACED_OPERATORS; // To undo padding operators in string literals

    Tokenizer();

public:

    // Breaking down the input into a list of meaningful words and operators
    static vector<Token> tokenize(string in);

};


// String helper Functions
int stringToInt(const string& str);

bool isQuoted(const string& str);

bool isAlnum(const string& str);

// This function assumes that the input is quoted. It doesn't modify the object
string removeQuotes(const string& str);
