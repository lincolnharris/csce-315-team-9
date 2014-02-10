<<<<<<< HEAD

=======
>>>>>>> 7f43335645aabef52e63c6659e55f1e0b138a07d
// Class Includes
#include "DBMS.h"
#include "Comparison.h"

<<<<<<< HEAD
=======
// Other Includes
>>>>>>> 7f43335645aabef52e63c6659e55f1e0b138a07d
#include <iostream>

using namespace std;


/******************** Constructor / Destructor *******************************/
DBMS::DBMS()
{
	// Nothing
}


DBMS::~DBMS()
{
	// Nothing
}



/******************** DBMS General Commands *******************************/
//Table DBMS::open_cmd(string name)
//{
//
//
//}
//
//
//void DBMS::close_cmd(string name)
//{
//
//
//}
//
//
//void DBMS::write_cmd(string name)
//{
//
//
//}
//
//
//void DBMS::exit_cmd()
//{
//
//
//}
//
//
//void DBMS::show_cmd(string name)
//{
//
//
//}
//



/******************** Table Manipulation *******************************/
<<<<<<< HEAD
void DBMS::create_cmd(string name, Type attributes[], string primaryKey[])
=======
void DBMS::create_cmd(string name, vector<Type> attributes, vector<string> primaryKey)
>>>>>>> 7f43335645aabef52e63c6659e55f1e0b138a07d
{
	// Lincoln
}


void DBMS::delete_cmd(Table table, Comparison cond)
{
	// Lincoln
}



<<<<<<< HEAD
// pair< attrb_index, value >
void DBMS::update_cmd(Table table, vector< pair<int, string> > fieldsToUpdate, 
						Comparison cond) 
=======
void DBMS::update_cmd(Table table, vector<pair<int, string>> fieldsToUpdate, Comparison cond) // tuple<attributeName, Value>
>>>>>>> 7f43335645aabef52e63c6659e55f1e0b138a07d
{
	// Dmitry
	for(vector<string>& row : table.rows)
		if(cond(row))
			for(int i = 0; i < fieldsToUpdate.size(); ++i)
				row[fieldsToUpdate[i].first] = fieldsToUpdate[i].second; 
}



<<<<<<< HEAD
void DBMS::insert_cmd(string name, string values[])
=======
void DBMS::insert_cmd(Table table, vector<string> values)
>>>>>>> 7f43335645aabef52e63c6659e55f1e0b138a07d
{
	// Shayan
}



void DBMS::insert_cmd(Table table, Table fromRelation)
{
	// Shayan
}




/******************** Table Logic Algebra *******************************/
Table DBMS::selection(Comparison cond, Table relation)
{
	// Lincoln
}



<<<<<<< HEAD
Table DBMS::projection(string attributes[], Table relation)
=======
Table DBMS::projection(vector<string> attributes, Table relation)
>>>>>>> 7f43335645aabef52e63c6659e55f1e0b138a07d
{
	// Lincoln
}



<<<<<<< HEAD
Table DBMS::renaming(string attributes[], Table relation)
=======
Table DBMS::renaming(vector<string> attributes, Table relation)
>>>>>>> 7f43335645aabef52e63c6659e55f1e0b138a07d
{

}



Table DBMS::union_(Table table1, Table table2)
{
	// Dmitry

	// Make new copies of table, to manipulate then display
<<<<<<< HEAD
	Table t1 = table1;
	Table t2 = table2;
=======
	Table t1 = rel1;
	Table t2 = rel2;
>>>>>>> 7f43335645aabef52e63c6659e55f1e0b138a07d

	// Does t1 & t2 have same number of attributs?
	if (t1.attributeMap.size() != t2.attributeMap.size())
	{
		cerr << "Not union Compatible" << endl;
		return;
	}

	// Do both have the same type of attributes?
	string name;
	for (int i = 0; i < t1.attributeMap.size(); i++)
	{
		if (t2.attributeMap.find(t1.attributeMap.at[i]) == t2.attributeMap.end())
		{
			cerr << "Attributes do not match" << endl;
		}
	}
	
	// Do the attributes index/location match for t1 & t2?
	Type type;
	// iterate through every attribute index
	for (int i = 0; i < t1.attributeMap.size(); i++)
	{
		// If indexes not the same, must relocate
		if ( t1.attributeMap.at[i] != t2.attributeMap.at[i] )
		{
			// Find attribute in t2
			type = t2.attributeMap.find[t1.attributeMap.at[i]];

			// move attrb values to corresponding indx to t1
			for(vector<string> row : t2.rows)
			{
				row.insert(row.begin() + i, row[type.index]);
				row.erase(row.begin() + type.index);
			}

			t2.attributeMap.at[i] = t2.attributeMap.at[type.index];
			t2.attributeMap.erase(t2.attributeMap.at[type.index]);
		}
	}


	bool duplicate = false;
	// Union the tables, while checking for duplicates
	for (int i = 0; i < t2.rows.size(); i++)
	{
		for(vector<string> row1 : t1.rows)	// check t1 
		{
			for(vector<string> row2 : t2.rows) // with all of t2 entries
			{
				if ( row1[0] == row2[0])
					duplicate = true;
			}

			// No duplicate found, copy t1[0] into t2.front
			if (!duplicate)
			{
				t2.rows.push_front(row1);
			}

			// If duplicate found or not, remove t1[0]
			t1.rows.erase(t1.rows.begin());

			// Reset duplicate
			duplicate = false;
		}
	}
	return t2;
}



Table DBMS::difference(Table table1, Table table2)
{

	// Dmitry
	
<<<<<<< HEAD
	Table t1 = table1;
	Table t2 = table2;
=======
	Table t1 = rel1;
	Table t2 = rel2;
>>>>>>> 7f43335645aabef52e63c6659e55f1e0b138a07d
	
	// Does t1 & t2 have same number of attributs?
	if (t1.attributeMap.size() != t2.attributeMap.size())
	{
		cerr << "Not union Compatible" << endl;
		return;
	}

	// Do both have the same type of attributes?
	string name;
	for (int i = 0; i < t1.attributeMap.size(); i++)
	{
		if (t2.attributeMap.find(t1.attributeMap.at[i]) == t2.attributeMap.end())
		{
			cerr << "Attributes do not match" << endl;
		}
	}
	
	// Do the attributes index/location match for t1 & t2?
	Type type;
	// iterate through every attribute index
	for (int i = 0; i < t1.attributeMap.size(); i++)
	{
		// If indexes not the same, must relocate
		if ( t1.attributeMap.at[i] != t2.attributeMap.at[i] )
		{
			// Find attribute in t2
			type = t2.attributeMap.find[t1.attributeMap.at[i]];

			// move attrb values to corresponding indx to t1
			for(vector<string> row : t2.rows)
			{
				row.insert(row.begin() + i, row[type.index]);
				row.erase(row.begin() + type.index);
			}

			t2.attributeMap.at[i] = t2.attributeMap.at[type.index];
			t2.attributeMap.erase(t2.attributeMap.at[type.index]);
		}
	}
	// Both tables have same order of attribute types

	// Copy current t1, clean its list, use to fill final table to return
	Table difference = t1;
	t1.rows.erase(t1.rows.begin(), t1.rows.end());

	bool duplicate = false;

	// Subtract 
	for (int i = 0; i < t1.rows.size(); i++)
	{
		for(vector<string> row1 : t1.rows)	// check t1 
		{
			for(vector<string> row2 : t2.rows) // with all of t2 entries
			{
				if ( row1[0] == row2[0] )	// only need to check first value
				{
					duplicate = true;
				}
			}

			if (!duplicate)
			{
				difference.rows.push_back(row1);
			}

			// Reset duplicate
			duplicate = false;
		}

<<<<<<< HEAD
=======
		return difference;
>>>>>>> 7f43335645aabef52e63c6659e55f1e0b138a07d
}



Table DBMS::cross_product(Table rel1, Table rel2)
{
	// Shayan
}



Table DBMS::natural_join(Table rel1, Table rel2)
{
	// Dmitry
}


