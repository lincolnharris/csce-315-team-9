/*
 * ParsedResult.h
 *
 *  Created on: Feb 16, 2014
 *      Author: Synix
 */

#pragma once
#include <string>

// This class is basically used whenever a parser function needs to
// return a value, which is either false (indicating failure) or the
// successful parsing of an object.
template<typename T>
class ParsedResult
{
    bool failed;
    T    result;
    //TODO might need optimization, shared pointer/regular pointer/reference

public:

    ParsedResult(bool boolean)
    {
        if(boolean == true)
            throw "ParsedResult can either be 'false' or a parsed object.";
        else failed = true;
    }

    ParsedResult(T result) : result(result), failed(false) {}

    operator bool() { return true; }

    operator T&()
    {
        if(failed) throw "Failed parsing operation does not have a value.";
        return result;
    }

    bool isSuccessful() { return !failed; }
};

