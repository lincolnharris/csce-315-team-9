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

using namespace std;


// Basically a string without unwanted content
struct Token
{
    string s;

    Token() = default;
    Token(string token) : s(token) {}
    Token(const char* token) : s(token) {}

    operator string&() { return s; }

    bool isQuoted(const string& s)
    {
        return (s[0] == '"' && s.back() == '"');
    }

    // This function assumes that the input is quoted
    // It doesn't modify the object
    string removeQuotes()
    {
        return s.substr(1, s.length() - 1);
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

