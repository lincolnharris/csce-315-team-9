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

using namespace std;


// Basically a string without unwanted content
struct Token
{
    string str;

	Token() {};
    Token(string token) : str(token) {}
    Token(const char* token) : str(token) {}

    operator string&() { return str; }

    bool isQuoted()
    {
        return (str[0] == '"' && str.back() == '"');
    }

    bool isAlnum()
    {
        return all_of(str.begin(), str.end(), [](char c) { return isalnum(c); });
    }

    // This function assumes that the input is quoted
    // It doesn't modify the object
    string removeQuotes()
    {
        return str.substr(1, str.length() - 1);
    }
};

// Functions that help tokenize the input
class Tokenizer
{
    // Order matters! E.g. if ">" matches first, then ">=" will never find a match [REGEX]
    static const regex OPERATORS;

public:

    // Breaking down the input into a list of meaningful words and operators
    static vector<Token> tokenize(const string& in);

};

