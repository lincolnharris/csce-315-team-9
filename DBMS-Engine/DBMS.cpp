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
	pair<string, Table> temp_table(name, table);
	relations.insert( temp_table );
}


void DBMS::delete_cmd(Table table, Comparison cond)
{// Lincoln
	for( list<vector<string>>::iterator it = table.rows.begin(); it != table.rows.end(); ++it){//go through each row
		if ( cond(*it) ) table.rows.erase(it);//if the row passes the condition, delete the row
	}	
}

/******************** Table Logic Algebra *******************************/
Table DBMS::selection(Comparison cond, Table table)
{// Lincoln
	Table selected;
	selected.attributeMap = table.attributeMap;
	for( list<vector<string>>::iterator it = table.rows.begin(); it != table.rows.end(); ++it){ //go through each row
		if ( cond(*it) ) selected.rows.push_back(*it);	//if the row passes the condition add it to the new table
	}
	return selected;
}



Table DBMS::projection(vector<string> attributes, Table table)
{// Lincoln
	Table proj;
	/*
	int numOfAtts = attributes.size();
	int numOfRows = table.rows.size();
	vector<Type> types;
	list<vector<strings> > lines;
	for(int i=0; i<numOfRows; ++i;){
		vector<string> temp;
		lines.push_back(temp);
	}
	for(int i=0; i<numOfAtts; ++i){	//go through all the wanted attributes
		unordered_map<string,Type>::const_iterator it = table.attributeMap.find(attributes[i]);//get itterator to the attribute
		
		}
	}
	*/
	return proj;
}
