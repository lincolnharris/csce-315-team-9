#pragma once

// Default Include
#include <string>
#include <unordered_map>

// Class Includes
#include "Table.h"

using namespace std;

class Comparison;
// TODO how to handle conditions? Combining Function Objects returning bool?

class DBMS
{

private:

    unordered_map<string, Table> relations; 	// Constructor....

public:

    DBMS();
    ~DBMS();

    //    Table open_cmd(string name);
    //    void close_cmd(string name);
    //    void write_cmd(string name);
    //    void exit_cmd();
    //    void show_cmd(string name);
    void create_cmd(string name, vector<Type> attributes, vector<string> primaryKey);
    void delete_cmd(string name, Comparison cond);
    void update_cmd(string name, vector<pair<int, string>> fieldsToUpdate, Comparison cond); // pair<attributeName, Value>
    void insert_cmd(string name, vector<string> values);
    void insert_cmd(string name, Table fromRelation);

    Table selection(Comparison cond, Table relation);
    Table projection(vector<string> attributes, Table relation);
    Table renaming(vector<string> attributes, Table relation);
    Table union_(Table rel1, Table rel2);
    Table difference(Table rel1, Table rel2);
    Table cross_product(Table rel1, Table rel2);
    Table natural_join(Table rel1, Table rel2);

};
