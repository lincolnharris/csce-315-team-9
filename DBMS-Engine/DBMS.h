#pragma once

// Default Include
#include <string>
#include <unordered_map>

// Class Includes
#include "Table.h"

using namespace std;

<<<<<<< HEAD

class Comparison; // TODO how to handle conditions? Combining Function Objects returning bool?
=======
class Comparison;
// TODO how to handle conditions? Combining Function Objects returning bool?
>>>>>>> 7f43335645aabef52e63c6659e55f1e0b138a07d

class DBMS
{

<<<<<<< HEAD
	private:

	    unordered_map<string, Table> _relation; 	// Constructor....

	public:

	    DBMS();
	    ~DBMS();


	    Table open_cmd(string name);
	    void close_cmd(string name);
	    void write_cmd(string name);
	    void exit_cmd();
	    void show_cmd(string name);



	    void create_cmd(string name, Type attributes[], string primaryKey[]);
	    void delete_cmd(string name, Condition cond);

		// tuple<attributeName, Value>
	    void update_cmd(Table table, vector< pair<int, string> > fieldsToUpdate, Comparison cond) ; 
	    void insert_cmd(Table table, string values[]);
	    void insert_cmd(Table table, Table fromRelation);

	    Table selection(Condition cond, Table relation);
	    Table projection(string attributes[], Table relation);
	    Table renaming(string attributes[], Table relation);
	    Table union_(Table rel1, Table rel2);
	    Table difference(Table rel1, Table rel2);
	    Table cross_product(Table rel1, Table rel2);
	    Table natural_join(Table rel1, Table rel2);
=======
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
    void delete_cmd(Table table, Comparison cond);
    void update_cmd(Table table, vector<pair<int, string>> fieldsToUpdate, Comparison cond); // pair<attributeName, Value>
    void insert_cmd(Table table, vector<string> values);
    void insert_cmd(Table table, Table fromRelation);

    Table selection(Comparison cond, Table relation);
    Table projection(vector<string> attributes, Table relation);
    Table renaming(vector<string> attributes, Table relation);
    Table union_(Table rel1, Table rel2);
    Table difference(Table rel1, Table rel2);
    Table cross_product(Table rel1, Table rel2);
    Table natural_join(Table rel1, Table rel2);
>>>>>>> 7f43335645aabef52e63c6659e55f1e0b138a07d

};
