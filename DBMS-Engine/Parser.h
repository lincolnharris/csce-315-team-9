
#pragma once

// Default Include
#include <string>
#include <unordered_map>

// Class Includes
#include "DBMS.h"
#include "ParsedResult.h"
#include "Table.h"
#include "Tokenizer.h"
#include "Comparison.h"

class Comparison;

class Parser
{

	private:	

		//

	public:

	// Queries	// not finished TEMPLATE PARAMETERS
	ParsedResult<Table>		query (vector<Token> tokens);
	ParsedResult<string>	relation_name (vector<Token> tokens);
	ParsedResult<string>	identifier (vector<Token> tokens);
	ParsedResult<char>		alpha (vector<Token> tokens);
	ParsedResult<int>		digit (vector<Token> tokens);
	ParsedResult<Table>		expr (vector<Token> tokens);
	ParsedResult<Table>		atomic_expr (vector<Token> tokens);
	ParsedResult<Table>		selection (vector<Token> tokens);
	ParsedResult<Condition>	condition (vector<Token> tokens);
	ParsedResult<Table>		conjunction (vector<Token> tokens);
	ParsedResult<Comparison>comparison (vector<Token> tokens);
	ParsedResult<char>		op (vector<Token> tokens);
	ParsedResult<string>	operand (vector<Token> tokens);
	ParsedResult<string>	attribute_name (vector<Token> tokens);
	ParsedResult<string>	literal (vector<Token> tokens);
	ParsedResult<Table>		projection (vector<Token> tokens);
	ParsedResult<string>	attribute_list (vector<Token> tokens);
	ParsedResult<Table>		renaming (vector<Token> tokens);
	ParsedResult<Table>		union__ (vector<Token> tokens);
	ParsedResult<Table>		difference (vector<Token> tokens);
	ParsedResult<Table>		product (vector<Token> tokens);
	ParsedResult<Table>		natural_join (vector<Token> tokens);

	// Commands
	bool			open_cmd (vector<Token> tokens);
	bool			close_cmd  (vector<Token> tokens);
	bool			write_cmd (vector<Token> tokens);
	bool			exit_cmd (vector<Token> tokens);
	bool			show_cmd (vector<Token> tokens);	
	bool			create_cmd (vector<Token> tokens);
	bool			update_cmd (vector<Token> tokens);
	bool			insert_cmd (vector<Token> tokens);
	bool			delete_cmd (vector<Token> tokens);
	ParsedResult<vector<string>>	type_attribute_list (vector<Token> tokens);
	ParsedResult<Type>	type (vector<Token> tokens);
	ParsedResult<int>	integer (vector<Token> tokens);
	ParsedResult<Table>	program (vector<Token> tokens);	
};



