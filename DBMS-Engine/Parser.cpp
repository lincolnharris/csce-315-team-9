

// Class Include
#include "Parser.h"


using namespace std;


ParsedResult	Parser::query (vector<Token> tokens)
{

}


ParsedResult<string>	Parser::relation_name (vector<Token> tokens)
{

}



ParsedResult	Parser::identifier (vector<Token> tokens)
{

}



ParsedResult<char>	Parser::alpha (vector<Token> tokens)
{

}


ParsedResult<int>	Parser::digit (vector<Token> tokens)
{

}


ParsedResult	Parser::expr (vector<Token> tokens)
{

}



ParsedResult	Parser::atomic_expr (vector<Token> tokens)
{

}



ParsedResult<Table>	Parser::selection (vector<Token> tokens)
{

}


ParsedResult<conditinon>	Parser::condition (vector<Token> tokens)
{

}



ParsedResult<Table>	Parser::conjunction (vector<Token> tokens)
{

}



ParsedResult<Comparison>	Parser::comparison (vector<Token> tokens)
{

}


ParsedResult<char>	Parser::op (vector<Token> tokens)
{

}


ParsedResult<string>	Parser::operand (vector<Token> tokens)
{

}



ParsedResult<sring>	Parser::attribute_name (vector<Token> tokens)
{

}



ParsedResult<string>	Parser::literal (vector<Token> tokens)
{

}



ParsedResult<Table>	Parser::projection (vector<Token> tokens)
{

}



ParsedResult<string>	Parser::attribute_list (vector<Token> tokens)
{

}


ParsedResult<Table>	Parser::renaming (vector<Token> tokens)
{

}


ParsedResult<Table>	Parser::union (vector<Token> tokens)
{

}


ParsedResult<Table>	Parser::difference (vector<Token> tokens)
{

}


ParsedResult<Table>	Parser::product (vector<Token> tokens)
{

}


ParsedResult<Table>	Parser::natural_join (vector<Token> tokens)
{

}


// Commands
bool	Parser::open_cmd (vector<Token> tokens)
{

}


bool	Parser::close_cmd  (vector<Token> tokens)
{

}


bool	Parser::write_cmd (vector<Token> tokens)
{

}


bool	Parser::exit_cmd (vector<Token> tokens)
{

}


bool	Parser::show_cmd (vector<Token> tokens)
{

}


	
bool	Parser::create_cmd (vector<Token> tokens)
{

}


bool	Parser::update_cmd (vector<Token> tokens)
{

}



bool	Parser::insert_cmd (vector<Token> tokens)
{

}


bool	Parser::delete_cmd (vector<Token> tokens)
{

}



ParsedResult	Parser::type_attribute_list (vector<Token> tokens)
{

}


ParsedResult	Parser::type (vector<Token> tokens)
{

}



ParsedResult	Parser::integer (vector<Token> tokens)
{

}



ParsedResult	Parser::program (vector<Token> tokens)
{

}



