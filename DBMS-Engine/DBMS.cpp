// Class Includes
#include "DBMS.h"


using namespace std;

/******************** Table Manipulation *******************************/
void DBMS::create_cmd(string name, vector< pair<string,Type> > attributes, vector<string> primaryKey)
{// Lincoln
	Table table;
	int size = attributes.size();
	for(int i=0; i<size; ++i){	//go through each attribute and add it to the attribute map
		pair<string,Type> temp(attributes[i]);
		table.attributeMap.insert( temp );
	}
	table.keys = primaryKey;
	relation[name] = table;
}


void DBMS::delete_cmd(Table table, Comparison cond)
{// Lincoln
	for( auto it = table.rows.begin(); it != table.rows.end(); ++it){//go through each row
		if ( cond(*it) ) table.rows.erase(it);//if the row passes the condition, delete the row
	}	
}

/******************** Table Logic Algebra *******************************/
Table DBMS::selection(Comparison cond, Table table)
{// Lincoln
	Table selected;
	selected.attributeMap = table.attributeMap;
	for( auto it = table.rows.begin(); it != table.rows.end(); ++it){ //go through each row
		if ( cond(*it) ) selected.rows.push_back(*it);	//if the row passes the condition add it to the new table
	}
	return selected;
}



Table DBMS::projection(vector<string> attributes, Table table)
{// Lincoln
	Table proj;
	int numOfAtts = attributes.size();
	int numOfRows = table.rows.size();
	list<vector<strings> > lines;	//hold the rows for the project for now
	for(int i=0; i<numOfRows; ++i;){//set up all the rows for the projection, but leave them empty for now
		vector<string> temp;
		lines.push_back(temp);
	}
	for(int i=0; i<numOfAtts; ++i){	//go through all the wanted attributes
		auto it = table.find (attributes[i]); //get an iterator to the Type of the attribute
		auto itA = lines.begin(); //iterator to the row where the attribute needs to be inserted
		auto itB = table.rows.begin(); //iterator to the attribute that needs to be inserted into new table
		for(int j=0; j<numOfRows; ++j){	//go through every row
			itA->push_back( (*itB)[ (it->second).index ] ); //add the correct string, based on the types index, from the old table to the projection
			++itA;	//go to next line for the projection
			++itB;	//go to next line for the old table
		}
		Type temp = it->second;
		temp.index = i;	//change the index of the type to the new index
		proj.attributeMap[attributes[i]] = temp; //add the attribute to the projection
		
	}
	proj.rows = lines;	//add all of the rows to the project
	return proj;
}
