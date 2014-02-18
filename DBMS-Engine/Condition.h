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

    // Takes in a row and recursively applies the condition tree on the row
    virtual bool operator()(const vector<string>& row) = 0;

};

class Comparison : public Condition
{
public:
    //          ==   !=   <    >   <=    >=
    enum Type { EQ, INEQ, LT, GT, LTEQ, GTEQ };

    Comparison(Condition* left, Type op, Condition* right);

    virtual bool operator()(const vector<string>& row);

private:
    Type node;
};

class Logical : public Condition
{
public:
    enum Type { OR, AND };

    Logical(Condition* left, Type op, Condition* right);

    virtual bool operator()(const vector<string>& row);

private:
    Type node;
};

class Operand : public Condition
{
public:

    string operand;

    Operand(string operand);

    virtual bool operator()(const vector<string>& row);
};
