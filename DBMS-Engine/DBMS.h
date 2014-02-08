#pragma once

// Default Include
#include <string>
#include <unordered_map>

// Class Includes
#include "Table.h"

using namespace std;


class Condition; // TODO how to handle conditions? Combining Function Objects returning bool?

class DBMS
{

private:

    unordered_map<string, Table> relations; 	// Constructor....

public:

    DBMS();
    ~DBMS();

    Table open_cmd(string name);
    void close_cmd(string name);
    void write_cmd(string name);
    void exit_cmd();
    void show_cmd(string name);
    void create_cmd(string name, Type[] attributes, string[] primaryKey);
    void update_cmd(string name, tuple<string, string> fieldsToUpdate, Condition cond); // tuple<attributeName, Value>
    void insert_cmd(string name, string[] values);
    void insert_cmd(string name, Table fromRelation);
    void delete_cmd(string name, Condition cond);

    Table selection(Condition cond, Table relation);
    Table projection(string[] attributes, Table relation);
    Table renaming(string[] attributes, Table relation);
    Table union_(Table rel1, Table rel2);
    Table difference(Table rel1, Table rel2);
    Table cross_product(Table rel1, Table rel2);
    Table natural_join(Table rel1, Table rel2);

};
