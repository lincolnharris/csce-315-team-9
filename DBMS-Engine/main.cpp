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
#include "Parser.h"

using namespace std;



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
    // Testing parsing and evaluation of Conditions
    DBMS db;
    db.relations["Test"] = Table();
    Table& t = db.relations["Test"];
    t.attributeMap["Age"] = Type(0, -1);
    t.attributeMap["First_Name"] = Type(1, 10);
    t.attributeMap["Tree"] = Type(2, -1);
    t.attributeMap["Flower"] = Type(3, 10);

    t.rows.push_back({ "44", "John", "44", "Pine" });
    t.rows.push_back({ "21", "John", "12345", "PotatoZ ARE cOOL" });
    t.rows.push_back({ "19", "Johnny", "19", "Pine" });
    t.rows.push_back({ "17", "Johnny", "17", "PotatoZ ARE cOOL" });

    vector<Token> tokens = Tokenizer::tokenize("(Age == Tree &&  \"Pine\" == Flower) || First_Name == \"Johnny\" ");
    Parser p(tokens, &db);
    Condition& cond = *p.condition();

    auto it = t.rows.begin();
    if(!cond(*it, t)) throw "";

    it++;
    if(cond(*it, t)) throw "";

    it++;
    if(!cond(*it, t)) throw "";

    it++;
    if(!cond(*it, t)) throw "";
    return 1;

    // TESTING TOKENIZER!
//    string in = "INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);";
//    string in = "common_names <- project (name) (select (aname == name && akind != kind) (a * animals));";
    string in = "dogs <-select(kind == \"dog + shit such>\\\"vow\")            animals;";
//    string in = "INSERT \"hello how are you good sir?";
    cout << in << endl;
    for(string s : Tokenizer::tokenize(in))
        cout << s << " ' ";
    cout << endl;
    return 1;

    for(string& s : Tokenizer::tokenize("old_dogs <- select (age> 10>==<=) dogs;"))
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
