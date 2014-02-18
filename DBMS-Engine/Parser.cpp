

// Class Include
#include "Parser.h"


using namespace std;


ParsedResult<Table>	Parser::query (vector<Token> tokens)
{
	return NULL;
}


ParsedResult<string>	Parser::relation_name (vector<Token> tokens)
{
	return NULL;
}



ParsedResult<string>	Parser::identifier (vector<Token> tokens)
{
	return NULL;
}



ParsedResult<char>	Parser::alpha (vector<Token> tokens)
{
	return " ";
} 


ParsedResult<int>	Parser::digit (vector<Token> tokens)
{
	return NULL;
}


ParsedResult<Table>	Parser::expr (vector<Token> tokens)
{
	return NULL;
}



ParsedResult<Table>	Parser::atomic_expr (vector<Token> tokens)
{
	return NULL;
}



ParsedResult<Table>	Parser::selection (vector<Token> tokens)
{
	return NULL;
}


ParsedResult<string>	Parser::condition (vector<Token> tokens)
{
	return NULL;
}



ParsedResult<Table>	Parser::conjunction (vector<Token> tokens)
{
	return NULL;
}



ParsedResult<string>	Parser::comparison (vector<Token> tokens)
{
	return NULL;
}


ParsedResult<char>	Parser::op (vector<Token> tokens)
{
	return " ";
}


ParsedResult<string>	Parser::operand (vector<Token> tokens)
{
	return NULL;
}



ParsedResult<string>	Parser::attribute_name (vector<Token> tokens)
{
	return NULL;
}



ParsedResult<string>	Parser::literal (vector<Token> tokens)
{
	return NULL;
}



ParsedResult<Table>	Parser::projection (vector<Token> tokens)
{
	return NULL;
}



ParsedResult<string>	Parser::attribute_list (vector<Token> tokens)
{
	return NULL;
}


ParsedResult<Table>	Parser::renaming (vector<Token> tokens)
{
	return NULL;
}


ParsedResult<Table>	Parser::union__ (vector<Token> tokens)
{
	return NULL;
}


ParsedResult<Table>	Parser::difference (vector<Token> tokens)
{
	return NULL;
}


ParsedResult<Table>	Parser::product (vector<Token> tokens)
{
	return NULL;
}


ParsedResult<Table>	Parser::natural_join (vector<Token> tokens)
{
	return NULL;
}


// Commands
bool	Parser::open_cmd (vector<Token> tokens)
{
	return NULL;
}


bool	Parser::close_cmd  (vector<Token> tokens)
{
	return NULL;
}


bool	Parser::write_cmd (vector<Token> tokens)
{
	return NULL;
}


bool	Parser::exit_cmd (vector<Token> tokens)
{
	return NULL;
}


bool	Parser::show_cmd (vector<Token> tokens)
{
	return NULL;
}


	
bool	Parser::create_cmd (vector<Token> tokens)
{
	return NULL;
}


bool	Parser::update_cmd (vector<Token> tokens)
{
	return NULL;
}



bool	Parser::insert_cmd (vector<Token> tokens)
{
	return NULL;
}


bool	Parser::delete_cmd (vector<Token> tokens)
{
	return NULL;
}



ParsedResult<vector<string>>	Parser::type_attribute_list (vector<Token> tokens)
{
	return NULL;
}


ParsedResult<Type>	Parser::type (vector<Token> tokens)
{
	return NULL;
}



ParsedResult<int>	Parser::integer (vector<Token> tokens)
{
	return NULL;
}



ParsedResult<Table>	Parser::program (vector<Token> tokens)
{
	return NULL;
}




