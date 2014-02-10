
// Class Includes
#include "DBMS.h"

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
Table DBMS::open_cmd(string name)
{


}


void DBMS::close_cmd(string name)
{


}


void DBMS::write_cmd(string name)
{


}


void DBMS::exit_cmd()
{


}


void DBMS::show_cmd(string name)
{


}




/******************** Table Manipulation *******************************/
void DBMS::create_cmd(string name, Type attributes[], string primaryKey[])
{
	// Lincoln
}


void DBMS::delete_cmd(string name, Condition cond)
{
	// Lincoln
}



// pair< attrb_index, value >
void DBMS::update_cmd(Table table, vector< pair<int, string> > fieldsToUpdate, 
						Comparison cond) 
{
	// Dmitry
	for(vector<string>& row : table.rows)
		if(cond(row))
			for(int i = 0; i < fieldsToUpdate.size(); ++i)
				row[fieldsToUpdate[i].first] = fieldsToUpdate[i].second; 
}



void DBMS::insert_cmd(string name, string values[])
{
	// Shayan
}



void DBMS::insert_cmd(string name, Table fromRelation)
{
	// Shayan
}




/******************** Table Logic Algebra *******************************/
Table DBMS::selection(Condition cond, Table relation)
{
	// Lincoln
}



Table DBMS::projection(string attributes[], Table relation)
{
	// Lincoln
}



Table DBMS::renaming(string attributes[], Table relation)
{
	// Shayan
}



Table DBMS::union_(Table t1, Table t2)
{
	// Dmitry
	
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
	
	// Do the attributes index/location match?
	Type type;
	// iterate through every attribute index
	for (int i = 0; i < t1.attributeMap.size(); i++)
	{
		// If indexes not the same, must relocate
		if ( t1.attributeMap.at[i] != t2.attributeMap.at[i] )
		{
			// Find attribute in t2
			type = t2.attributeMap.find[t1.attributeMap.at[i]];

			// Now re-organize/shift contents in t2 to match t1 attrbMap

		}
	}

}



Table DBMS::difference(Table rel1, Table rel2)
{
	// Dmitry
}



Table DBMS::cross_product(Table rel1, Table rel2)
{
	// Shayan
}



Table DBMS::natural_join(Table rel1, Table rel2)
{
	// Dmitry
}


