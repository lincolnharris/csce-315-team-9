#pragma once

// Default Include
#include <string>
#include <unordered_map>

// Class Includes
#include "Table.h"

using std::string;
using std::vector;
using std::pair;
using std::list;

class Condition;

class DBMS
{



public:
    unordered_map<string, Table> relations; 	// Constructor....

    DBMS();
    ~DBMS();

    Table open_cmd(string name);
    void close_cmd(string name);
	void write_cmd(string name);
    void exit_cmd();
    void show_cmd(Table& table);
    void create_cmd(string name, vector<pair<string, Type>>& attributes, vector<string>& primaryKey);
    void delete_cmd(string name);
    void delete_cmd(Table& table, Condition& cond);
    void update_cmd(Table& table, vector<pair<int, string>>& fieldsToUpdate, Condition& cond); // pair<attributeName, Value>
    void insert_cmd(Table& table, vector<string> values);
    void insert_cmd(Table& table, const Table& fromRelation);

    Table selection(Condition& cond, const Table& relation);
    Table projection(vector<string>& attributes, const Table& relation);
    Table renaming(vector<string>& attributes, const Table& relation);
    Table union_(const Table& t1, const Table& t2);
    Table difference(const Table& t1, const Table& t2);
    Table cross_product(const Table& t1, const Table& t2);
    Table natural_join(Table& t1, Table& t2);

    // App Interaction
    list<vector<string>> execute(string input); // Returns multiple lines of output, if any.
};

// Helper Function
bool is_union_compatible(const Table& t1, const Table& t2);
