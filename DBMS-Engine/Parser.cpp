
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


ParsedResult<Comparison> Parser::relation_name()
{
	
	return NULL;
}



ParsedResult<Table>	Parser::expr()
{
	return NULL;
}



ParsedResult<Table>	Parser::atomic_expr()
{
	return NULL;
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
	counter++;

	// close )
	if(tokens[counter].str != ")")
	{
		counter = start;
		return false;
	}
	counter++;
	
	//  now check relation name
	auto& atomic_expr_result = atomic_expr();
	if (!atomic_expr_result)
	{
		counter = start;
		return false;
	} 
	counter++;

	Table tempT = dbms->selection(condition_result,														atomic_expr_result);

	return tempT;
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
	if (tokens[counter].isAlnum)
	{
		counter++;
		return tokens[counter].str;
	}
	


}



ParsedResult<Table>	Parser::projection()
{
	int start = counter;

	if (tokens[counter].str != "project")
	{
		return false;
	}
	counter++;

	if (tokens[counter].str != "(")
	{
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

	// Find if table exists
	bool found_table = false;
	Table table;
	for(auto& database : dbms->relations)
	{
		if (database.first == tokens[counter].str)
		{
			table = database.second;
			found_table = true;
			counter++;
		}
	}

	if (!found_table)
	{
		counter = start;
		return false;
	}

	return dbms->projection(Atrb_List, table);
}



ParsedResult<vector<string>>	Parser::attribute_list()
{

	if (tokens[counter] != )
	{

	}
}


ParsedResult<Table>	Parser::renaming()
{
	// takes a lot of parameters
	return NULL;
}


ParsedResult<Table>	Parser::union__()
{
	return NULL;
}


ParsedResult<Table>	Parser::difference()
{
	return NULL;
}


ParsedResult<Table>	Parser::product()
{
	return NULL;
}


ParsedResult<Table>	Parser::natural_join()
{
	return NULL;
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
