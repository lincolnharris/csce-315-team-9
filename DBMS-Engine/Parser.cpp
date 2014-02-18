// Class Include
#include "Parser.h"
#include "DBMS.h"

#include <regex>

Parser::Parser(vector<Token>& tokens, DBMS* dbms) : tokens(tokens), dbms(dbms), counter(0)
{
}

ParsedResult<Comparison*> Parser::condition()
{
    int start = counter; // Saving where we started from in case we need to backtrack
    auto conj_result = conjunction();
    if(!conj_result)
    {
        counter = start; // Backtrack
        return false;
    }

    Comparison* compTree = conj_result;

    while(true)
    {
        if(tokens[counter].str == "||")
        {
            counter++;
            auto conj_result_list = conjunction();
            if(!conj_result)
            {
                counter = start; // Backtrack
                return false;
            }
            compTree = new Comparison(OR, compTree, conj_result_list);
        }
        else break;
    }
    return compTree;
}

ParsedResult<Comparison*> Parser::conjunction()
{
    int start = counter; // Saving where we started from in case we need to backtrack
    auto comp_result = comparison();
    if(!comp_result)
    {
        counter = start; // Backtrack
        return false;
    }

    Comparison* compTree = comp_result;

    while(true)
    {
        if(tokens[counter].str == "&&")
        {
            counter++;
            auto comp_result_list = comparison();
            if(!comp_result)
            {
                counter = start; // Backtrack
                return false;
            }
            compTree = new Comparison(AND, compTree, comp_result_list);
        }
        else break;
    }
    return compTree;
}


ParsedResult<Comparison*> Parser::comparison1()
{
    // operand op operand
    int start = counter; // Saving where we started from in case we need to backtrack
    auto operand1_result = operand();
    if(!operand1_result)
    {
        counter = start; // Backtrack
        return false;
    }

    auto op_result = op();
    if(!op_result)
    {
        counter = start; // Backtrack
        return false;
    }

    auto operand2_result = operand();
    if(!operand2_result)
    {
        counter = start; // Backtrack
        return false;
    }

    // Create the Condition object

    string op = op_result;
    if(op == "==")
    {
        return new Condition([](const vector<string>& row) {
           return true;
        });
    }

    counter = start;
    return false;
}
//== | != | < | > | <= | >=
ParsedResult<Comparison*> Parser::comparison2()
{
    int start = counter;
    if(tokens[counter].str != "(")
    {
        counter = start;
        return false;
    }
    counter++;

    auto condition_result = condition();
    if(!condition_result)
    {
        counter = start; // Backtrack
        return false;
    }

    if(tokens[counter].str != ")")
    {
        counter = start;
        return false;
    }
    counter++;

    return condition_result;
}

ParsedResult<Comparison*> Parser::comparison()
{
    int start = counter; // Saving where we started from in case we need to backtrack
    auto comp_result = comparison1();
    if(comp_result)
    {
        return comp_result;
    }
    else
    {
        comp_result = comparison2();
        if(comp_result)
        {
            return comp_result;
        }
    }
    counter = start; // Backtrack
    return false;
}

ParsedResult<string> Parser::op()
{
    int start = counter; // Saving where we started from in case we need to backtrack
    string op_result = tokens[counter];
    if(!regex_match(op_result, regex("==|!=|<=|>=|<|>")))
    {
        counter = start; // Backtrack
        return false;
    }
    counter++;

    return op_result;
}

ParsedResult<string> Parser::operand()
{
}
