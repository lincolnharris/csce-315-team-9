/*
 * Table.h
 *
 *  Created on: Feb 8, 2014
 *      Author: Synix
 */

#pragma once

#include <string>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;


struct Type
{
    int   index;
    short type;     // -1 == int, anything positive is a string of that length

    Type() {}
    Type(int index, short type) : index(index), type(type) {}
};

class Table
{
	
	public:

		vector<string> keys;
	    unordered_map<string, Type> attributeMap;   // Mapping <attribute name> to <column index, data type>

	    list<vector<string>>        rows;           // The table is stored as a linked list of rows
	                                                // each row is an array of strings
	                                                // each string holds the value of its respective column


	    // Helper functions for the future!
	    int getInt();
	    string getString();

	    Table();
	    ~Table();
};

