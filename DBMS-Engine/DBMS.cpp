// Class Includes
#include "DBMS.h"


using namespace std;

/******************** Table Manipulation *******************************/
void DBMS::create_cmd(string name, vector<Type> attributes, vector<string> primaryKey)
{// Lincoln
	Table table;
	table.attributeMap = attributes;
	table.keys = primaryKey;
	relations.insert( {name , table} );
}


void DBMS::delete_cmd(Table table, Condition cond)
{// Lincoln
	for( list<vector<string>>::iterator it = table.rows.begin(); it != table.rows.end(); ++it){
		if ( cond(*it) ) table.rows.erase(it);
	}	
}

/******************** Table Logic Algebra *******************************/
Table DBMS::selection(Condition cond, Table table)
{// Lincoln
	Table selected;
	selected.attributeMap = table.attributeMap;
	selected.keys = table.keys;
	for( list<vector<string>>::iterator it = table.rows.begin(); it != table.rows.end(); ++it){
		if ( cond(*it) ) selected.rows.push_back(*it);	
	}
}



Table DBMS::projection(vector<string> attributes, Table table)
{// Lincoln
	Table proj;
	proj.attributeMap = table.attributeMap;
	proj.keys = table.keys;
	proj.rows = table.rows;
	int numOfColumns = proj.attributeMap.size();
	int numOfAtts = attributes.size();
	for(int i=0; i<numOfColumns; ++i){
		bool found = false;
		for(int j=0; (j<numOfAtts || !(found) ); ++j){
			if( (proj.attributeMap)[i].attrb_name == attributes[j] ) found = true;
		}
		if( !(found) ){
			for( vector<string> row : proj.rows){
				row.erase(row.begin() + i);
			}
			proj.attributeMap.erase(proj.attributeMap.begin()+i);
			--i;
		}
	}
}
