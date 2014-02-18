
// Class Include
#include "Parser.h"
#include "DBMS.h"


using namespace std;

Parser::Parser(vector<Token>& tokens, DBMS* dbms = nullptr) : tokens(tokens), dbms(dbms)
{}

ParsedResult<Table>	Parser::query()
{
	
	return NULL;
}


ParsedResult<string> Parser::relation_name()
{
	int start = counter;

	string result;
	result = identifier();
	if (!result)
	{
		counter = start;
		return false;
	}

	return result;
}



ParsedResult<Table>	Parser::expr()
{
	int start = counter;

	// atomic expression, OR one of the following operations
	// check if atomic expression

	if (tokens[counter].str == "selection")
	{
		table = selection();
	}

	else if ( (tokens[counter].str == "project") ||
		 (tokens[counter].str == "rename") )
	{
		table = project_AND_rename();
	}

	else if ( (tokens[counter].s == "union") ||
		 (tokens[counter].s == "difference") ||
		 (tokens[counter].s == "natural-join") ||
		 (tokens[counter].s == "project") )
	{
		table = relational_algebra();
	}

	else
	{
		counter = start;
		return false;
	}

	return table;
}



ParsedResult<Table>	Parser::atomic_expr()
{
	int start = counter;

	Table table
	// Is current word a TABLE?
	if (dbms->relations.find(tokens[counter].str) != 
							dbms->relations.end())
	{
		// then table found
		table = dbms->relations.find(tokens[counter].str)->second;
		counter++;
	}

	// Is current word a EXPRESSION?
	else
	{	
		if (tokens[counter].str != "(")
		{
			counter = start;
			return false;
		}
		counter++;

		table = expr();
		if (!table)
		{
			counter = start;
			return false;
		}

		if (tokens[counter].str != ")")
		{
			counter = start;
			return false;
		}
		counter++;
	}

	return table;
}



ParsedResult<Table>	Parser::selection() 
{
	// select 
	int start = counter;
	if(tokens[counter].str != "select")
	{
		// Select did not exist/work, return completely
		return false;
	}
	counter++;

	// first (
	if(tokens[counter].str != "(")
	{
		counter = start;
		return false;
	}
	counter++;

	// condition
	auto& condition_result = condition();
	if(!condition_result)
	{
		counter =  start;
		return false;
	}

	// close )
	if(tokens[counter].str != ")")
	{
		counter = start;
		return false;
	}
	counter++;
	
	//  now check relation name
	Table table;
	table = atomic_expr();
	if (!table)
	{
		counter = start;
		return false;
	}

	return dbms->selection(condition_result, table);
}


ParsedResult<Condition>	Parser::condition()
{
	// shay
	return NULL;
}



ParsedResult<Comparison>	Parser::conjunction()
{
	// shay
	return NULL;
}



ParsedResult<Comparison>	Parser::comparison()
{
	// shay
	return NULL;
}


ParsedResult<char>	Parser::op()
{
	// shay
	return " ";
}


ParsedResult<string>	Parser::operand()
{
	// shay
	return NULL;
}


ParsedResult<string>	Parser::attribute_name()
{
	int start = counter;

	if (!tokens[counter].isAlnum())
	{
		counter = start;
		return false;
	}

	return tokens[counter].str;
}



ParsedResult<Table>	Parser::project_AND_rename() /////////////////////////////////
{
	// Project/Rename:: = ( attribute-list) atomic_expr

	int start = counter;

	// Is it project or rename
	string Op;
	if ( (tokens[counter].str == "project") ||
		 (tokens[counter].str == "rename") )
	{
		Op =  tokens[counter].str;
		counter++;
	}
	else	// not project OR rename
	{
		counter = start;
		return false;
	}
	

	// is next string (
	if (tokens[counter].str != "(")
	{
		counter = start;
		return false;
	}
	counter++;


	// Find attribute list
	vector<string> Atrb_List;
	Atrb_List = attribute_list();
	if (!attribute_list())
	{
		counter = start;
		return false;
	}

	if (tokens[counter].str != ")")
	{
		counter = start;
		return false;
	}
	counter++;

	// Read atomic_expr
	Table table;
	table = atomic_expr();
	if (!table)
	{
		counter = start;
		return false;
	}

	if (Op == "project")
	{
		return dbms->projection(Atrb_List, table);
	}

	if (Op == "rename")
	{
		return dbms->rename(Atrb_List, table);
	}
}



ParsedResult<vector<string>>	Parser::attribute_list()
{
	/*
	int start = counter;

	// grab attribute name
	auto tempString = attribute_name();
	if (!tempString )
	{
		return false;
	}
	*/
}


// Union, Diff, Projection, NaturalJoin
ParsedResult<Table>	Parser::relational_algebra()
{
	// is next word a table name? or is it another expression
	int start = counter;
	
	// Takes Table OR expression
	// either result is a table
	Table table1;
	Table table2;

	// Read first atomic expr
	table1 = atomic_expr();
	if (!table1)
	{
		counter = start;
		return false;
	}

	// Store operator for the operation
	string Op = tokens[counter].str;
	counter++;

	// Read second atomic expr
	table2 = atomic_expr();
	if (!table2)
	{
		counter = start;
		return false;
	}

	switch	(Op)
	{
		case "+": return dbms->union_(table1, table2);
		case "-": return dbms->differene(table1, table2);
		case "*": return dbms->product(table1, table2);
		case "J": return dbms->natural_join(table1, table2);	 // Join
		default:	return false;
	}
}


// Commands
bool	Parser::open_cmd()
{
	return NULL;
}


bool	Parser::close_cmd()
{
	return NULL;
}


bool	Parser::write_cmd()
{
	return NULL;
}


bool	Parser::exit_cmd()
{
	return NULL;
}


bool	Parser::show_cmd()
{
	return NULL;
}


	
bool	Parser::create_cmd()
{
	return NULL;
}


bool	Parser::update_cmd()
{
	return NULL;
}



bool	Parser::insert_cmd()
{
	return NULL;
}


bool	Parser::delete_cmd()
{
	return NULL;
}



ParsedResult<vector<string>> Parser::type_attribute_list()
{
	return NULL;
}


ParsedResult<Type>	Parser::type()
{
	return NULL;
}



ParsedResult<int>	Parser::integer()
{
	// uses digit
	return NULL;
}



ParsedResult<Table>	Parser::program()
{
	return NULL;
}
