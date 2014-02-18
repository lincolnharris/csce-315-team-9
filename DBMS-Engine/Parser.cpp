

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


ParsedResult<string>	Parser::relation_name()
{
	
	return NULL;
}



ParsedResult<string>	Parser::identifier()
{
	// alpha is in here
	
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
	// select ( condition ) 
	int start = counter;
	if(tokens[counter].s != "select")
	{
		return false;
	}
		return false; // We popped something! We should somehow put it back in, OR not
			// pop it in the first place! and only pop things out if the match is successful
	counter++;
	
	if(tokens[counter].s != "(")
		return false;
	counter++;

	if(condition())
		return false;
	counter++;
	return tokens >> "select" >> "(" >> condition() >> ")" >> Success;
	return NULL;
}


ParsedResult<string>	Parser::condition()
{
	return NULL;
}



ParsedResult<Table>	Parser::conjunction()
{
	return NULL;
}



ParsedResult<string>	Parser::comparison()
{
	return NULL;
}


ParsedResult<char>	Parser::op()
{
	return " ";
}


ParsedResult<string>	Parser::operand()
{
	return NULL;
}



ParsedResult<string>	Parser::attribute_name()
{
	return NULL;
}



ParsedResult<string>	Parser::literal()
{
	string valid_string;
	valid_string = tokens[0].operator std::string &;

	return valid_string;
}



ParsedResult<Table>	Parser::projection()
{
	return NULL;
}



ParsedResult<string>	Parser::attribute_list()
{
	return NULL;
}


ParsedResult<Table>	Parser::renaming()
{
	// takes a lot of parameters
	return NULL;
}


ParsedResult<Table>	Parser::union__()
{
	// union two tables

	// Check if tables exist


	Table t1 = tokens[0].operator std::string &;
	Table t2 = tokens[1].operator std::string &;

	return union_(t1, t2);
}


ParsedResult<Table>	Parser::difference()
{
	// difference two tables
	Table t1 = tokens[0].operator std::string &;
	Table t2 = tokens[1].operator std::string &;

	return difference(t1, t2);

}


ParsedResult<Table>	Parser::product()
{
	// product two tables
	for ()
	{

	}

	Table t1 = tokens[0].operator std::string &;
	Table t2 = tokens[1].operator std::string &;

	return product(t1, t2);
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


bool Tables_Exists(Table t1, Table t2)
{
	bool check1 = false;
	bool check2 = false;
	for(auto& table1 : dbms)
		if 
}