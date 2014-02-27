// Class Include
#include "Parser.h"
#include "DBMS.h"

#include <regex>
#include <iostream>

using namespace std;


Parser::Parser(vector<Token> tokens, DBMS* dbms) : tokens(tokens), dbms(dbms), counter(0)
{
}


/////////////// SHAYAN //////////////////////////////////
ParsedResult<Condition*> Parser::condition()
{
    int start = counter; // Saving where we started from in case we need to backtrack
    auto conj_result = conjunction();
    if(!conj_result)
    {
        counter = start; // Backtrack
        return false;
    }

    Condition* condTree = conj_result;

    while(true)
    {
        if(match("||"))
        {
            auto conj_result_list = conjunction();
            if(!conj_result_list)
            {
                delete condTree;
                counter = start; // Backtrack
                return false;
            }
            condTree = new Logical(condTree, Logical::Type::OR, conj_result_list);
        }
        else break;
    }
    cout << condTree->toString() << endl; //DEBUG
    return condTree;
}

ParsedResult<Condition*> Parser::conjunction()
{
    int start = counter; // Saving where we started from in case we need to backtrack
    auto comp_result = comparison();
    if(!comp_result)
    {
        counter = start; // Backtrack
        return false;
    }

    Condition* condTree = comp_result;

    while(true)
    {
        if(match("&&"))
        {
            auto comp_result_list = comparison();
            if(!comp_result)
            {
                delete condTree;
                counter = start; // Backtrack
                return false;
            }
            condTree = new Logical(condTree, Logical::Type::AND, comp_result_list);
        }
        else break;
    }
    return condTree;
}


ParsedResult<Condition*> Parser::comparison1()
{
    // operand op operand
    int start = counter; // Saving where we started from in case we need to backtrack
    auto operand1_result = operand();
    if(!operand1_result)
    {
        counter = start; // Backtrack
        return false;
    }

    auto op_result = op();
    if(!op_result)
    {
        counter = start; // Backtrack
        return false;
    }

    auto operand2_result = operand();
    if(!operand2_result)
    {
        counter = start; // Backtrack
        return false;
    }

    // Create the Condition object
    typedef Operand::Type OPT;
    pair<string, bool> op1 = operand1_result, op2 = operand2_result;
    OPT op1t = op1.second ? OPT::ATTRIBUTE : OPT::LITERAL;
    OPT op2t = op2.second ? OPT::ATTRIBUTE : OPT::LITERAL;
    return new Comparison(new Operand(op1.first, op1t), op_result, new Operand(op2.first, op2t));
}

ParsedResult<Condition*> Parser::comparison2()
{
    // ( condition )
    int start = counter;
    if(!match("("))
    {
        counter = start;
        return false;
    }

    auto condition_result = condition();
    if(!condition_result)
    {
        counter = start; // Backtrack
        return false;
    }

    if(!match(")"))
    {
        counter = start;
        return false;
    }

    return condition_result;
}

ParsedResult<Condition*> Parser::comparison()
{
    int start = counter; // Saving where we started from in case we need to backtrack
    auto comp_result = comparison1();
    if(comp_result)
        return comp_result;

    comp_result = comparison2();
    if(comp_result)
        return comp_result;

    counter = start; // Backtrack
    return false;
}

ParsedResult<string> Parser::op()
{
    int start = counter; // Saving where we started from in case we need to backtrack
    if(counter >= tokens.size()) return false;

    string op_result = tokens[counter];
    if(!regex_match(op_result, regex("==|!=|<=|>=|<|>")))
    {
        counter = start; // Backtrack
        return false;
    }
    counter++;

    cout << (string)op_result << endl;
    return op_result;
}

ParsedResult<pair<string, bool>> Parser::operand()
{
    int start = counter; // Saving where we started from in case we need to backtrack
    auto attname_result = attribute_name();
    if(attname_result)
        return pair<string, bool>(attname_result, true);

    auto literal_result = literal();
    if(literal_result)
        return pair<string, bool>(literal_result, false);

    counter = start; // Backtrack
    return false;
}

ParsedResult<string> Parser::literal()
{
    int start = counter; // Saving where we started from in case we need to backtrack
    if(counter < tokens.size() && isQuoted(tokens[counter]))
        return (string)tokens[counter++];

    auto int_result = integer();
    if(int_result)
        return to_string((int)int_result);

    counter = start; // Backtrack
    return false;
}

bool Parser::delete_relation_cmd()
{
    int start = counter; // Saving where we started from in case we need to backtrack
    if(!match("DELETE"))
    {
        counter = start; // Backtrack
        return false;
    }

    auto relname_result = relation_name();
    if(!relname_result)
    {
        counter = start; // Backtrack
        return false;
    }

    dbms->delete_cmd(relname_result);
    return true;
}

ParsedResult<vector<string>> Parser::attribute_list()
{
    int start = counter; // Saving where we started from in case we need to backtrack
    auto attribute_result = attribute_name();
    if(!attribute_result)
    {
        counter = start; // Backtrack
        return false;
    }

    vector<string> attributeList;
    attributeList.push_back(attribute_result);
    while(true)
    {
        if(match(","))
        {
            auto attribute_result = attribute_name();
            if(!attribute_result)
            {
                counter = start; // Backtrack
                return false;
            }
            attributeList.push_back(attribute_result);
        }
        else break;
    }
    return attributeList;
}

ParsedResult<Table> Parser::query()
{
    //relation-name <- expr
    int start = counter; // Saving where we started from in case we need to backtrack

    auto relname_result = relation_name();
    if(!relname_result)
    {
        counter = start; // Backtrack
        return false;
    }

    if(!match("<-"))
    {
        counter = start; // Backtrack
        return false;
    }

    auto expr_result = expr();
    if(!expr_result)
    {
        counter = start; // Backtrack
        return false;
    }

    if(dbms->relations.find(relname_result) != dbms->relations.end())
        throw "A relation with this name already exists!";
    dbms->relations[relname_result] = expr_result;
    return expr_result;
}

bool Parser::command()
{
    int start = counter; // Saving where we started from in case we need to backtrack
    auto result = open_cmd();
    if(result) return true;

    result = close_cmd();
    if(result) return true;

    result = write_cmd();
    if(result) return true;

    result = exit_cmd();
    if(result) return true;

    result = show_cmd();
    if(result) return true;

    result = create_cmd();
    if(result) return true;

    result = update_cmd();
    if(result) return true;

    result = insert_cmd();
    if(result) return true;

    result = delete_cmd();
    if(result) return true;

    counter = start; // Backtrack
    return false;
}

ParsedResult<Table> Parser::program()
{
    int start = counter; // Saving where we started from in case we need to backtrack
    Table result;

    auto query_result = query();
    if(query_result)
    {
        result = query_result;
    }
    else
    {
        auto cmd_result = command();
        if(cmd_result)
            result = Table();
        else throw "Could not parse!";
    }
    if(match(";"))
        return result;

    throw "Could not parse!";
}

bool Parser::match(string match)
{
    if(counter < tokens.size() && tokens[counter] == match)
    {
        counter++;
        return true;
    }
    return false;
}


///////////////////////// LINCOLN /////////////////////////////
bool Parser::open_cmd(){
    int start = counter;

    if ( !match("OPEN") ){
        counter = start;
        return false;
    }

    auto name = relation_name();
    if (!name)
    {
        counter = start; // Backtrack
        return false;
    }
    dbms->open_cmd(name);
    return true;
}

bool Parser::close_cmd(){
    int start = counter;

    if ( !match("CLOSE") ){
        counter = start;
        return false;
    }

    auto name = relation_name();
    if (!name)
    {
        counter = start; // Backtrack
        return false;
    }
    dbms->close_cmd(name);
    return true;
}

bool Parser::write_cmd(){
    int start = counter;

    if ( !match("WRITE") ){
        counter = start;
        return false;
    }

    auto name = relation_name();
    if (!name)
    {
        counter = start; // Backtrack
        return false;
    }
    dbms->write_cmd(name);
    return true;
}

bool Parser::exit_cmd(){
    int start = counter;

    if ( !match("EXIT") ){
        counter = start;
        return false;
    }
    dbms->exit_cmd();
    return true;
}

bool Parser::show_cmd(){
    int start = counter;

    if ( !match("SHOW") ){
        counter = start;
        return false;
    }

    auto table = atomic_expr();
    if (!table)
    {
        counter = start; // Backtrack
        return false;
    }

    dbms->show_cmd(table);
    return true;
}

bool Parser::create_cmd(){
    int start = counter;
    if ( !match("CREATE") ){
        counter = start;
        return false;
    }
    if ( !match("TABLE") ){
        counter = start;
        return false;
    }
    auto name = relation_name();
    if (!name)
    {
        counter = start; // Backtrack
        return false;
    }
    if ( !match("(") ){
        counter = start;
        return false;
    }
    auto typed_att_list = typed_attribute_list();
    if (!typed_att_list){
        counter = start;
        return false;
    }
    if ( !match(")") ){
        counter = start;
        return false;
    }
    if ( !match("PRIMARY") ){
        counter = start;
        return false;
    }
    if ( !match("KEY") ){
        counter = start;
        return false;
    }
    if ( !match("(") ){
        counter = start;
        return false;
    }
    auto att_list = attribute_list();
    if (!att_list){
        counter = start;
        return false;
    }
    if ( !match(")") ){
        counter = start;
        return false;
    }
    dbms->create_cmd(name, typed_att_list, att_list);
    return true;
}

bool Parser::update_cmd(){
    int start = counter;

    if ( !match("UPDATE") ){
        counter = start;
        return false;
    }

    auto Rname = relation_name();
    if (!Rname){
        counter = start;
        return false;
    }

    if ( !match("SET") ){
        counter = start;
        return false;
    }

    auto Aname = attribute_name();
    if (!Aname){
        counter = start;
        return false;
    }

    if ( !match("=") ){
        counter = start;
        return false;
    }

    auto lit = literal();
    if (!lit){
        counter = start;
        return false;
    }

    vector<pair<int, string>> fieldsToUpdate;
    auto it = dbms->relations.find(Rname);
    if(it == dbms->relations.end() ) throw("No table with the name " + Rname);
    auto Ait = it->second.attributeMap.find(Aname);
    if(Ait == it->second.attributeMap.end() ) throw("Attribute not foud");
    fieldsToUpdate.push_back(pair<int,string>( Ait->second.index, lit ));

    while (true){
        int tempStart = counter;

        if ( !match(",") ){
            counter = tempStart;
            break;
        }

        Aname = attribute_name();
        if (!Aname) {
            counter = tempStart;
            break;
        }
        if ( !match("=") ){
            counter = tempStart;
            break;
        }
        lit = literal();
        if (!lit) {
            counter = tempStart;
            break;
        }
        Ait = it->second.attributeMap.find(Aname);
        if(Ait == it->second.attributeMap.end() ) throw("Attribute not foud");
        fieldsToUpdate.push_back(pair<int,string>( Ait->second.index, lit ));
    }

    if ( !match("WHERE") ){
        counter = start;
        return false;
    }

    auto cond = condition();
    if (!cond) {
        counter = start;
        return false;
    }

    dbms->update_cmd(it->second,fieldsToUpdate, *cond);
    return true;
}

bool Parser::insert_cmd(){
    int start = counter;

    if ( !match("INSERT") ){
        counter = start;
        return false;
    }

    if ( !match("INTO") ){
        counter = start;
        return false;
    }

    auto name = relation_name();
    if (!name) {
        counter = start;
        return false;
    }

    if ( !match("VALUES") ){
        counter = start;
        return false;
    }
    if ( !match("FROM") ){
        counter = start;
        return false;
    }

    if ( match("RELATION") ){

        auto exp = expr();
        if (!exp){
            counter = start;
            return false;
        }
        unordered_map<string, Table>::iterator it = dbms->relations.find(name);
        dbms->insert_cmd(it->second, exp);
        return true;
    }
    else {
        if ( !match("(") ){
            counter = start;
            return false;
        }
        auto lit = literal();
        if (!lit){
            counter = start;
            return false;
        }
        vector<string> lits;
        lits.push_back(lit);

        while (true){
            int tempStart = counter;

            if ( !match(",") ){
                counter = tempStart;
                break;
            }
            lit = literal();
            if (!lit) {
                counter = tempStart;
                break;
            }
            lits.push_back(lit);
        }
        if ( !match(")") ){
            counter = start;
            return false;
        }
        unordered_map<string, Table>::iterator it = dbms->relations.find(name);
        dbms->insert_cmd( it->second, lits);
        return true;
    }
}

bool Parser::delete_cmd(){
    int start = counter;

    if ( !match("DELETE") ){
        counter = start;
        return false;
    }
    if ( !match("FROM") ){
        counter = start;
        return false;
    }

    auto name = relation_name();
    if (!name){
        counter = start;
        return false;
    }

    if ( !match("WHERE") ){
        counter = start;
        return false;
    }

    auto cond = condition();
    if (!cond){
        counter = start;
        return false;
    }
    auto it = dbms->relations.find(name);
    dbms->delete_cmd(it->second, *cond);
    return true;
}

ParsedResult<vector<pair<string, Type>>> Parser::typed_attribute_list(){
    int start = counter;
    auto name = attribute_name();
    if (!name){
        counter = start;
        return false;
    }
    auto t = type();
    if (!t){
        counter = start;
        return false;
    }
    vector<string> names;
    vector<Type> ts;
    names.push_back(name);
    ts.push_back(t);
    ts[ts.size()-1].index = ts.size()-1;
    while (true){
        int tempStart = counter;
        if ( !match(",") ){
            counter = tempStart;
            break;
        }
        name = attribute_name();
        if (!name) {
            counter = tempStart;
            break;
        }
        t = type();
        if (!t) {
            counter = tempStart;
            break;
        }
        names.push_back(name);
        ts.push_back(t);
        ts[ts.size()-1].index = ts.size()-1;
    }

    int size = names.size();
    vector<pair<string, Type> > result;
    for (int i = 0; i<size; ++i){
        pair<string, Type> temp(names[i], ts[i]);
        result.push_back(temp);
    }
    return result;
}

ParsedResult<Type> Parser::type(){
    int start = counter;
    if ( match("VARCHAR") ){
        if ( !match("(") ){
            counter = start;
            return false;
        }
        int integr = integer();
        if (!integr){
            counter = start;
            return false;
        }
        if ( !match(")") ){
            counter = start;
            return false;
        }
        return Type(0, integr);
    }
    else if ( match("INTEGER") ){
        return Type(0, -1);
    }
    else{
        counter = start;
        return false;
    }
}

ParsedResult<int> Parser::integer(){
    int start = counter;
    int integr = atoi(tokens[counter].str.c_str());
    if (integr == 0){
        counter = start;
        return false;
    }
    ++counter;
    return integr;
}


/////////////////// DMITRY /////////////////////////
ParsedResult<string> Parser::relation_name()
{
    int start = counter;

    auto result = attribute_name();
    if (!result)
    {
        counter = start;
        return false;
    }

    if (dbms->relations.find(result) == dbms->relations.end())
    {
        throw "Relation Not Found";
    }

    return result;
}



ParsedResult<Table> Parser::expr()
{
    int start = counter;

    // atomic expression, OR one of the following operations
    // check if atomic expression
    Table table;
    if ( match("select") )
    {
        table = selection();
    }

    else if ( match("project") || match("rename") )
    {
        table = project_AND_rename();
    }

    else if ( (match("union")) || match("difference") ||
          match("natural-join") || match("project") )
    {
        table = relational_algebra();
    }

    else // If current word is not an expression function
    {    // then it must be atomic expression
        auto atomic_table = atomic_expr();
        if( !atomic_table)
        {
            counter = start;
            return false;
        }
    }

    return table;
}


ParsedResult<Table> Parser::atomic_expr()
{
    int start = counter;

    Table table;
    
    // Is current word a TABLE?
    if (dbms->relations.find(tokens[counter].str) 
                        != dbms->relations.end())
    {
        // then table found
        table = dbms->relations.find(tokens[counter].str)->second;
        counter++;
        return table;
    }

    // Is current word a EXPRESSION?
    else
    {
        if ( !match("(") )
        {
            counter = start;
            return false;
        }

        auto express_table = expr();
        if (!express_table)
        {
            counter = start;
            return false;
        }

        if ( !match(")") )
        {
            counter = start;
            return false;
        }

    return express_table;
    }
}



ParsedResult<Table> Parser::selection()
{
    // select
    int start = counter;

    // first (
    if( !match("(") )
    {
        counter = start;
        return false;
    }

    // condition
    auto condition_result = condition();
    if(!condition_result)
    {
        counter =  start;
        return false;
    }

    // close )
    if( !match(")") )
    {
        counter = start;
        return false;
    }

    //  now check relation name
    auto table = atomic_expr();
    if (!table)
    {
        counter = start;
        return false;
    }
    Condition* temp = condition_result;
    return dbms->selection(*temp, table);
}

ParsedResult<string>    Parser::attribute_name()
{
    int start = counter;

    if (counter >= tokens.size() || !isAlnum(tokens[counter]))
    {
        counter = start;
        return false;
    }

    return (string)tokens[counter++];
}



ParsedResult<Table> Parser::project_AND_rename() /////////////////////////////////
{
    // Project/Rename:: = ( attribute-list) atomic_expr
    --counter;
    int start = counter;

    // Is it project or rename
    string Op;
    if ( (match("project")) || (match("rename")) )
    {
        Op =  tokens[counter-1]; // counter got incremented in match
    }
    else    // not project OR rename
    {
        counter = start;
        return false;
    }

    // is next string (
    if ( !match("(") )
    {
        counter = start;
        return false;
    }
    // Find attribute list
    auto Atrb_List = attribute_list();
    if (!Atrb_List)
    {
        counter = start;
        return false;
    }
    if ( !match(")") )
    {
        counter = start;
        return false;
    }
    // Read atomic_expr
    auto table = atomic_expr();
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
        return dbms->renaming(Atrb_List, table);
    }
}


// Union, Diff, Projection, NaturalJoin
ParsedResult<Table> Parser::relational_algebra()
{
    // is next word a table name? or is it another expression
    int start = counter;

    // Takes Table OR expression
    // either result is a table

    // Read first atomic expr
    auto table1 = atomic_expr();
    if (!table1)
    {
        counter = start;
        return false;
    }

    // Store operator for the operation
    string Op = tokens[counter].str;
    counter++;

    // Read second atomic expr
    auto table2 = atomic_expr();
    if (!table2)
    {
        counter = start;
        return false;
    }

    switch  (Op[0])
    {
        case '+': return dbms->union_(table1, table2);
        case '-': return dbms->difference(table1, table2);
        case '*': return dbms->cross_product(table1, table2);
        case 'J': 
            if(Op == "Join")
                return dbms->natural_join(table1, table2);     // Join
        default:    counter = start; return false;
    }
}
