#pragma once

// Default Include
#include <string>
#include <unordered_map>

// Class Includes
#include "ParsedResult.h"
#include "Table.h"
#include "Tokenizer.h"
#include "Condition.h"
#include "DBMS.h"

class Parser
{

private:

    vector<Token> tokens;
    DBMS* dbms;
    int counter;

public:

    // Constructor
    Parser(vector<Token> tokens, DBMS* dbms = nullptr);

    // Queries
    // PARAMETERS NEED TO BE CORRECTED
    ParsedResult<Table> query();
    ParsedResult<string> relation_name();
    ParsedResult<string> identifier();
    ParsedResult<Table> expr();
    ParsedResult<Table> atomic_expr();
    ParsedResult<Table> selection();
    ParsedResult<Condition*> condition();
    ParsedResult<Condition*> conjunction();
    ParsedResult<Condition*> comparison1();
    ParsedResult<Condition*> comparison2();
    ParsedResult<Condition*> comparison();
    ParsedResult<string> op();

    // The string is the parsed value, the boolean indicates whether it's a
    // literal (false) or an attribute name (true)
    ParsedResult<pair<string, bool>> operand();

    ParsedResult<string> attribute_name();
    ParsedResult<string> literal();
    ParsedResult<Table> projection();
    ParsedResult<vector<string>> attribute_list();
    ParsedResult<Table> renaming();
    ParsedResult<Table> union__();
    ParsedResult<Table> difference();
    ParsedResult<Table> product();
    ParsedResult<Table> natural_join();
    ParsedResult<Table> project_AND_rename();
    ParsedResult<Table> relational_algebra();

    // Commands
    bool open_cmd();
    bool close_cmd();
    bool write_cmd();
    bool exit_cmd();
    bool show_cmd();
    bool create_cmd();
    bool update_cmd();
    bool insert_cmd();
    bool delete_cmd();
    ParsedResult<vector<pair<string, Type>>> typed_attribute_list();
    ParsedResult<Type> type();
    ParsedResult<int> integer();
    ParsedResult<Table> program();

    // Helper
    bool match(string toMatch);
};
