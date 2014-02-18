/*
 * Comparison.cpp
 *
 *  Created on: Feb 9, 2014
 *      Author: Synix
 */

#include "Condition.h"

Condition::Condition(Condition* left, Condition* right) :
        left(left), right(right)
{
}



Comparison::Comparison(Condition* left, Type op, Condition* right) :
        Condition(left, right), node(op)
{
}

bool Comparison::operator()(const vector<string>& row)
{
    if(node == EQ)
        return (*left)(row) == (*right)(row);
    else if(node == INEQ)
        return (*left)(row) != (*right)(row);
    else if(node == LT)
        return (*left)(row) <  (*right)(row);
    else if(node == LTEQ)
        return (*left)(row) <= (*right)(row);
    else if(node == GT)
        return (*left)(row) >  (*right)(row);
    else if(node == GTEQ)
        return (*left)(row) >= (*right)(row);

    else throw "Something went wrong!";
}

Logical::Logical(Condition* left, Type op, Condition* right) :
        Condition(left, right), node(op)
{
}

bool Logical::operator()(const vector<string>& row)
{
    if(node == AND)
        return (*left)(row) && (*right)(row);
    else if(node == OR)
        return (*left)(row) || (*right)(row);

    else throw "Something went wrong!";
}

Operand::Operand(string operand) :
        Condition(nullptr, nullptr), operand(operand)
{
}

bool Operand::operator()(const vector<string>& row)
{
}
