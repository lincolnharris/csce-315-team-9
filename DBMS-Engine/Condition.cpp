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



Comparison::Comparison(Condition* left, string op, Condition* right) :
        Condition(left, right), op(op)
{
}

bool Comparison::operator()(const vector<string>& row, const Table& table)
{
    if(op == "==")
        return (*left)(row, table) == (*right)(row, table);
    else if(op == "!=")
        return (*left)(row, table) != (*right)(row, table);
    else if(op == "<")
        return (*left)(row, table) <  (*right)(row, table);
    else if(op == "<=")
        return (*left)(row, table) <= (*right)(row, table);
    else if(op == ">")
        return (*left)(row, table) >  (*right)(row, table);
    else if(op == ">=")
        return (*left)(row, table) >= (*right)(row, table);

    else throw "Something went wrong!";
}



Logical::Logical(Condition* left, Type op, Condition* right) :
        Condition(left, right), node(op)
{
}

bool Logical::operator()(const vector<string>& row, const Table& table)
{
    if(node == AND)
        return (*left)(row, table) && (*right)(row, table);
    else if(node == OR)
        return (*left)(row, table) || (*right)(row, table);

    else throw "Something went wrong!";
}



Operand::Operand(string operand, Type type) :
        Condition(nullptr, nullptr), operand(operand), node(type)
{
}

bool Operand::operator()(const vector<string>& row, const Table& table)
{
//TODO
}
