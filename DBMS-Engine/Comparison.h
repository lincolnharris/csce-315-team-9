/*
 * Comparison.h
 *
 *  Created on: Feb 9, 2014
 *      Author: Synix
 */
#pragma once

#include <vector>
#include <functional>

using std::string;


enum NodeType { OR, AND, CONDITION };

class Comparison
{
public:

    NodeType node;
    Comparison* left;
    Comparison* right;

    Comparison(NodeType type, Comparison* left, Comparison* right);

    bool operator()(const vector<string>& row);
};

class Condition : public Comparison
{
public:
    // This is a function which can be applied to a row in the table
    // like age >= 21, or name == "John"
    typedef function<bool(const vector<string>&)> ConditionFunc;

    ConditionFunc condition;

    Condition(ConditionFunc condition);

    bool operator()(const vector<string>& row);
};
