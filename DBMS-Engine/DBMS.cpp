// Class Includes
#include "DBMS.h"


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
void DBMS::create_cmd(string name, vector<Type> attributes, vector<string> primaryKey)
{
	// Lincoln
}


void DBMS::delete_cmd(string name, Condition cond)
{
	// Lincoln
}



void DBMS::update_cmd(string name, pair<string, string> fieldsToUpdate, Condition cond) // tuple<attributeName, Value>
{
	// Dmitry
}



void DBMS::insert_cmd(string name, vector<string> values)
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



Table DBMS::projection(vector<string> attributes, Table relation)
{
	// Lincoln
}



Table DBMS::renaming(vector<string> attributes, Table relation)
{
	// Shayan
}



Table DBMS::union_(Table rel1, Table rel2)
{
	// Dmitry
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


