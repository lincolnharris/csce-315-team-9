
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

class Parser
{

	private:	

		vector<Token>& tokens;
		DBMS* dbms;
		int counter;

	public:

	// Constructor
	Parser(vector<Token>& tokens, DBMS* dbms = nullptr);

	// Queries	
	// PARAMETERS NEED TO BE CORRECTED
	ParsedResult<Table>		query();
	ParsedResult<string>	relation_name();
	ParsedResult<string>	identifier();
	ParsedResult<Table>		expr();
	ParsedResult<Table>		atomic_expr();
	ParsedResult<Table>		selection();
	ParsedResult<string>	condition();
	ParsedResult<Table>		conjunction();
	ParsedResult<string>	comparison();
	ParsedResult<char>		op();
	ParsedResult<string>	operand();
	ParsedResult<string>	attribute_name();
	ParsedResult<string>	literal();
	ParsedResult<Table>		projection();
	ParsedResult<string>	attribute_list();
	ParsedResult<Table>		renaming();
	ParsedResult<Table>		union__();
	ParsedResult<Table>		difference();
	ParsedResult<Table>		product();
	ParsedResult<Table>		natural_join();

	// Commands
	bool			open_cmd();
	bool			close_cmd();
	bool			write_cmd();
	bool			exit_cmd();
	bool			show_cmd();	
	bool			create_cmd();
	bool			update_cmd();
	bool			insert_cmd();
	bool			delete_cmd();
	ParsedResult<vector<string>>	type_attribute_list();
	ParsedResult<Type>	type();
	ParsedResult<int>	integer();
	ParsedResult<Table>	program();	
};

bool Tables_Exists (Table t1, Table t2);


