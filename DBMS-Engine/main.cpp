/*
 * main.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: Synix
 */

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include "ParsedResult.h"
#include "Tokenizer.h"

using namespace std;


struct Type
{
    int index;
    short type;     // -1 == int, anything positive is a string of that length

	Type() {};
    Type(int index, short type) :
            index(index), type(type)
    {
    }
};

ostream& operator<<(ostream& out, const Type& t)
{
    return out << '[' << t.index << " -> " << t.type << ']';
}

ParsedResult<int> test_ParsedResult()
{
    return 6;
}


int main()
{
    cout << (int)test_ParsedResult() << endl;

    for(string& s : Tokenizer().tokenize("old_dogs <- select (age> 10>==<=) dogs;"))
        cout << s << " | ";
    cout << endl;
    cout << (int)test_ParsedResult();
    return 1;

    unordered_map<string, Type> attributeMap;
    list<vector<string>> table;

    // Creating a very simple database
    vector<string> strings1{"45", "foo", "bar"};
    vector<string> strings2{"56", "remove", "bar"};
    vector<string> strings3{"2", "foo", "NOTbar"};
    attributeMap["Age"] = Type(0, -1); // First column, type integer (-1)
    table.push_back(strings1);
    table.push_back(strings2);
    table.push_back(strings3);

    // Reading from it: Ranged-based for loop
    int ageIndex = attributeMap["Age"].index;
    for(auto& row : table) // auto ~ vector<string>
        cout << row[ageIndex] << " - ";
    cout << endl;

    // OR : iterating through the list
    for(auto iter = table.begin(); iter != table.end(); iter++) // auto ~ list<vector<string>>::iterator
        cout << (*iter)[ageIndex] << " = ";
    cout << endl;

    // OR for_each loop, similar structure to sort, remove_if, transform (VERY useful funtions) all in <algorithm>
    // For the 3rd argument you could use lambda or any function object, basically anything with operator() defined
    for_each(table.begin(), table.end(), [ageIndex](vector<string>& row) {
        cout << row[ageIndex] << " + ";
    });
    cout << endl;

    // Another example
    table.remove_if([](vector<string>& row) {
        return row[1] == "remove";
    });
    for(auto row : table) cout << row[1] << " - ";
    cout << endl;

    // Yet another example: 3rd argument could be another container! E.g transform and store in another list
    transform(table.begin(), table.end(), table.begin(), [](vector<string>& row) {
        if(row[2] == "bar") row[2] = "CHANGED!";
        return row;
    });
    for(auto row : table) cout << row[2] << " - ";
    cout << endl;

    cout << attributeMap["Age"] << attributeMap["YanYan"] << endl;

    return 1;
}
