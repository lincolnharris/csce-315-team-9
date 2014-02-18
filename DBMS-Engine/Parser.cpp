// Class Include
#include "Parser.h"
#include "DBMS.h"

#include <regex>

Parser::Parser(vector<Token>& tokens, DBMS* dbms) : tokens(tokens), dbms(dbms), counter(0)
{
}

ParsedResult<Comparison*> Parser::condition()
{
//    condition ::= conjunction { || conjunction }
//
//    conjunction ::= comparison { && comparison }
//
//    comparison ::= operand op operand
//                         | ( condition )

}

ParsedResult<Comparison*> Parser::conjunction()
{
    int start = counter; // Saving where we started from in case we need to backtrack
    auto conj_result = comparison();
    if(!conj_result)
    {
        counter = start; // Backtrack
        return false;
    }
    counter++;

    Comparison* compTree = conj_result;

    while(true)
    {
        if(tokens[counter].str == "&&")
        {
            counter++;
            auto conj_result_list = comparison();
            if(!conj_result)
            {
                counter = start; // Backtrack
                return false;
            }
            counter++;
            compTree = new Comparison(AND, compTree, conj_result_list);
        }
        else break;
    }
    return compTree;
}

ParsedResult<Comparison*> Parser::comparison()
{
}

ParsedResult<string> Parser::op()
{
    int start = counter; // Saving where we started from in case we need to backtrack
    string op_result = tokens[counter];
    if(!regex_match(tokens[counter].str, regex("==|!=|<=|>=|<|>")))
    {
        counter = start; // Backtrack
        return false;
    }
    counter++;

    return op_result;
}
