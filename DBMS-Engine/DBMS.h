#pragma once

// Default Include
#include <string>
#include <unordered_map>

// Class Includes
#include "Table.h"

using namespace std;

class Comparison;

class DBMS
{



public:
    unordered_map<string, Table> relations; 	// Constructor....

    DBMS();
    ~DBMS();

    //    Table open_cmd(string name);
    //    void close_cmd(string name);
    //    void write_cmd(string name);
    //    void exit_cmd();
    //    void show_cmd(string name);
    void create_cmd(string name, vector<Type>& attributes, vector<string>& primaryKey);
    void delete_cmd(Table& table, Comparison& cond);
    void update_cmd(Table& table, vector<pair<int, string>>& fieldsToUpdate, Comparison& cond); // pair<attributeName, Value>
    void insert_cmd(Table& table, vector<string>& values);
    void insert_cmd(Table& table, const Table& fromRelation);

    Table selection(Comparison& cond, const Table& relation);
    Table projection(vector<string>& attributes, const Table& relation);
    Table renaming(vector<string>& attributes, const Table& relation);
    Table union_(const Table& rel1, const Table& rel2);
    Table difference(const Table& rel1, const Table& rel2);
    Table cross_product(const Table& rel1, const Table& rel2);
    Table natural_join(const Table& rel1, const Table& rel2);

};

// Helper Function
bool is_union_compatible(const Table& t1, const Table& t2);
