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
protected:
    Condition* left;
    Condition* right;

public:

    virtual ~Condition() = default;
    Condition() = default;
    Condition(Condition* left, Condition* right);

    void referenceTable(const Table& table);

    // Takes in a row and recursively applies the condition tree on the row
    virtual bool operator()(const vector<string>& row, const Table& table) = 0;

};

class Comparison : public Condition
{
public:

    Comparison(Condition* left, string op, Condition* right);

    virtual bool operator()(const vector<string>& row, const Table& table);

private:
    string op;
};

class Logical : public Condition
{
public:
    enum Type { OR, AND };

    Logical(Condition* left, Type op, Condition* right);

    virtual bool operator()(const vector<string>& row, const Table& table);

private:
    Type node;
};

class Operand : public Condition
{
public:
    enum Type { LITERAL, ATTRIBUTE };

    Operand(string operand, Type type);

    virtual bool operator()(const vector<string>& row, const Table& table);

private:
    string operand;
    Type   node;
};
