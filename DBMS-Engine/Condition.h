/*
 * Comparison.h
 *
 *  Created on: Feb 9, 2014
 *      Author: Synix
 */
#pragma once

#include <vector>
#include <functional>
#include <string>
#include "Tokenizer.h"
#include "Table.h"

using std::string;
using std::vector;


class Condition
{
public:
    Condition* left;
    Condition* right;

    virtual ~Condition() = default;
    Condition() = default;
    Condition(Condition* left, Condition* right);

    // Takes in a row and recursively applies the condition tree on the row
    virtual bool operator()(const vector<string>& row, const Table& table) = 0;

    // pair<value, type> :
    //      value could be an integer stored as a string or an actual string
    //      type is true for integers, false for strings
    virtual pair<string, bool> getValue(const vector<string>& row, const Table& table) = 0;
};

class Comparison : public Condition
{
public:
    string op;

    Comparison(Condition* left, string op, Condition* right);

    virtual bool operator()(const vector<string>& row, const Table& table);
    virtual pair<string, bool> getValue(const vector<string>& row, const Table& table);
};

class Logical : public Condition
{
public:
    enum Type { OR, AND };
    Type node;

    Logical(Condition* left, Type op, Condition* right);

    virtual bool operator()(const vector<string>& row, const Table& table);
    virtual pair<string, bool> getValue(const vector<string>& row, const Table& table);
};

class Operand : public Condition
{
public:
    enum Type { LITERAL, ATTRIBUTE };
    string operand;
    Type   node;

    Operand(string operand, Type type);

    virtual bool operator()(const vector<string>& row, const Table& table);
    virtual pair<string, bool> getValue(const vector<string>& row, const Table& table);
};
