/*
 * Comparison.cpp
 *
 *  Created on: Feb 9, 2014
 *      Author: Synix
 */

#include "Comparison.h"


Comparison::Comparison(NodeType type, Comparison* left, Comparison* right) :
    node(type), left(left), right(right)
{
}

Condition::Condition(ConditionFunc condition) :
        Comparison(CONDITION, nullptr, nullptr), condition(condition)
{
}

bool Comparison::operator()(vector<string>& row)
{
    if(node == AND)
        return (*left)(row) && (*right)(row);
    else if(node == OR)
        return (*left)(row) || (*right)(row);
    else throw "Comparison cannot be typed CONDITION";
}

bool Condition::operator ()(vector<string>& row)
{
    return condition(row);
}
