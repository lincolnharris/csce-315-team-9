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

Condition::~Condition()
{
    delete left;
    delete right;
}



Comparison::Comparison(Condition* left, string op, Condition* right) :
        Condition(left, right), op(op)
{
}

pair<string, bool> Comparison::getValue(const vector<string>& row, const Table& table)
{
    return (*this)(row, table) ? pair<string, bool>("1", true)
                               : pair<string, bool>("0", true);
}

bool Comparison::operator()(const vector<string>& row, const Table& table)
{
    const pair<string, bool>& lhs = left->getValue(row, table);
    const pair<string, bool>& rhs = right->getValue(row, table);

    if(lhs.second != rhs.second) throw "Operand types do not match!";

    if(lhs.second) // Integer types
    {
        int lhsInt = stringToInt(lhs.first);
        int rhsInt = stringToInt(rhs.first);
        if(op == "==")      return lhsInt == rhsInt;
        else if(op == "!=") return lhsInt != rhsInt;
        else if(op == "<")  return lhsInt <  rhsInt;
        else if(op == "<=") return lhsInt <= rhsInt;
        else if(op == ">")  return lhsInt >  rhsInt;
        else if(op == ">=") return lhsInt >= rhsInt;

        else throw "Something went wrong!";
    }

    // Literal string types
    if(op == "==")      return lhs.first == rhs.first;
    else if(op == "!=") return lhs.first != rhs.first;
    else if(op == "<")  return lhs.first <  rhs.first;
    else if(op == "<=") return lhs.first <= rhs.first;
    else if(op == ">")  return lhs.first >  rhs.first;
    else if(op == ">=") return lhs.first >= rhs.first;

    else throw "Something went wrong!";
}



Logical::Logical(Condition* left, Type op, Condition* right) :
        Condition(left, right), node(op)
{
}

pair<string, bool> Logical::getValue(const vector<string>& row, const Table& table)
{
    return (*this)(row, table) ? pair<string, bool>("1", true)
                               : pair<string, bool>("0", true);
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

pair<string, bool> Operand::getValue(const vector<string>& row, const Table& table)
{
    if(node == LITERAL)
    {
        if(isQuoted(operand)) // If it's a literal string, set the flag to false
            return pair<string, bool>(removeQuotes(operand), false);
        return pair<string, bool>(operand, true);
    }
    else if(node == ATTRIBUTE)
    {
        auto found = table.attributeMap.find(operand);
        if(found == table.attributeMap.end())
            throw '"' + operand + "\" not found!";

        const string& rowVal = row[found->second.index];
        if(found->second.type == -1)
            return pair<string, bool>(rowVal, true);
        return pair<string, bool>(rowVal, false);
    }
    else throw "Something went wrong!";
}

bool Operand::operator()(const vector<string>& row, const Table& table)
{
    throw "This function was not supposed to be called. Possible error in tree structure.";
}

string Comparison::toString()
{
    return '(' + left->toString() + ' ' + op + ' ' + right->toString() + ')';
}

string Logical::toString()
{
    return '(' + left->toString() + (node == OR ? " || " : " && ") + right->toString() + ')';
}

string Operand::toString()
{
    return operand;
}
