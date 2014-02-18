

// Class Include
#include "Parser.h"
#include "DBMS.h"


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



ParsedResult<vector<char>>	Parser::alpha (vector<Token> tokens)
{
	vector<char> valid_chars;
	for (int i = 0; i < tokens.size(); i++)
	{
		if (isalpha(tokens[i].operator std::string &) )
		{
			valid_chars.push_back(tokens[i].operator std::string &);
		}
	}

	// If nothing was added to vector_chars then no tokens were valid chars
	if (valid_chars.size() == 0)
	{
		return false;
	}

	return valid_chars;
} 


ParsedResult<vector<int>>	Parser::digit (vector<Token> tokens)
{
	vector<int> valid_int;
	for (int i = 0; i < tokens.size(); i++)
	{
		if (isdigit(tokens[i].operator std::string &) )
		{
			valid_int.push_back(tokens[i].operator std::string &);
		}
	}

	// If nothing was added to vector_int then all tokens were not int
	if (valid_int.size() == 0)
	{
		return false;
	}

	return valid_int;
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
	string valid_string;
	valid_string = tokens[0].operator std::string &;

	return valid_string;
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
	// takes a lot of parameters
	return NULL;
}


ParsedResult<Table>	Parser::union__ (vector<Token> tokens)
{
	// union two tables

	// Check if tables exist


	Table t1 = tokens[0].operator std::string &;
	Table t2 = tokens[1].operator std::string &;

	return union_(t1, t2);
}


ParsedResult<Table>	Parser::difference (vector<Token> tokens)
{
	// difference two tables
	Table t1 = tokens[0].operator std::string &;
	Table t2 = tokens[1].operator std::string &;

	return difference(t1, t2);

}


ParsedResult<Table>	Parser::product (vector<Token> tokens)
{
	// product two tables
	for ()
	{

	}

	Table t1 = tokens[0].operator std::string &;
	Table t2 = tokens[1].operator std::string &;

	return product(t1, t2);
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


bool Tables_Exists(Table t1, Table t2)
{
	bool check1 = false;
	bool check2 = false;
	for(auto& table1 : relations)..................
		if 
}