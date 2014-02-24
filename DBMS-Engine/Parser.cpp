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
    {
        Condition* ccp = comp_result;
        return comp_result;
    }
    else
    {
        comp_result = comparison2();
        if(comp_result)
        {
            Condition* ccp = comp_result;
            return comp_result;
        }
    }
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
    {
        return pair<string, bool>(attname_result, true);
    }
    else
    {
        auto literal_result = literal();
        if(literal_result)
        {
            return pair<string, bool>(literal_result, false);
        }
    }
    counter = start; // Backtrack
    return false;
}

ParsedResult<string> Parser::literal()
{
    int start = counter; // Saving where we started from in case we need to backtrack
    if(counter < tokens.size() && isQuoted(tokens[counter]))
    {
        return (string)tokens[counter++];
    }
    else
    {
        auto int_result = integer();
        if(int_result)
        {
            return to_string((int)int_result);
        }
    }
    counter = start; // Backtrack
    return false;
}


bool Parser::match(string toMatch)
{
    if(counter < tokens.size() && tokens[counter] == toMatch)
    {
        counter++;
        return true;
    }
    return false;
}


///////////////////////// LINCOLN /////////////////////////////
bool Parser::open_cmd(){
    int start = counter;

    if (tokens[counter].str != "OPEN"){
        counter = start;
        return false;
    }
    ++counter;

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

    if (tokens[counter].str != "CLOSE"){
        counter = start;
        return false;
    }
    ++counter;

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

    if (tokens[counter].str != "WRITE"){
        counter = start;
        return false;
    }
    ++counter;

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

    if (tokens[counter].str != "EXIT"){
        counter = start;
        return false;
    }
    ++counter;
    dbms->exit_cmd();
    return true;
}

bool Parser::show_cmd(){
    int start = counter;

    if (tokens[counter].str != "SHOW"){
        counter = start;
        return false;
    }
    ++counter;

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

    if (tokens[counter].str != "CREATE"){
        counter = start;
        return false;
    }
    ++counter;
    if (tokens[counter].str != "TABLE"){
        counter = start;
        return false;
    }
    ++counter;

    auto name = relation_name();
    if (!name)
    {
        counter = start; // Backtrack
        return false;
    }

    if (tokens[counter].str != "("){
        counter = start;
        return false;
    }
    ++counter;

    auto typed_att_list = typed_attribute_list();
    if (!typed_att_list){
        counter = start;
        return false;
    }

    if (tokens[counter].str != ")"){
        counter = start;
        return false;
    }
    ++counter;

    if (tokens[counter].str != "PRIMARY"){
        counter = start;
        return false;
    }
    ++counter;

    if (tokens[counter].str != "KEY"){
        counter = start;
        return false;
    }
    ++counter;

    if (tokens[counter].str != "("){
        counter = start;
        return false;
    }
    ++counter;

    auto att_list = attribute_list();
    if (!att_list){
        counter = start;
        return false;
    }
    ++counter;

    if (tokens[counter].str != ")"){
        counter = start;
        return false;
    }
    ++counter;

    dbms->create_cmd(name, typed_att_list, att_list);
    return true;
}

bool Parser::update_cmd(){
    int start = counter;

    if (tokens[counter].str != "UPDATE"){
        counter = start;
        return false;
    }
    ++counter;

    auto Rname = relation_name();
    if (!Rname){
        counter = start;
        return false;
    }

    if (tokens[counter].str != "SET"){
        counter = start;
        return false;
    }
    ++counter;

    auto Aname = attribute_name();
    if (!Aname){
        counter = start;
        return false;
    }

    if (tokens[counter].str != "="){
        counter = start;
        return false;
    }
    ++counter;

    auto lit = literal();
    if (!lit){
        counter = start;
        return false;
    }

    vector<string> Anames;
    Anames.push_back(Aname);
    vector<string> lits;
    lits.push_back(lit);

    while (true){
        int tempStart = counter;

        if (tokens[counter].str != ","){
            counter = tempStart;
            break;
        }

        Aname = attribute_name();
        if (!Aname) {
            counter = tempStart;
            break;
        }
        if (tokens[counter].str != "="){
            counter = tempStart;
            break;
        }
        ++counter;
        lit = literal();
        if (!lit) {
            counter = tempStart;
            break;
        }
        Anames.push_back(Aname);
        lits.push_back(lit);
    }

    if (tokens[counter].str != "WHERE"){
        counter = start;
        return false;
    }
    ++counter;

    auto cond = condition();
    if (!cond) {
        counter = start;
        return false;
    }


    unordered_map<string, Table>::iterator it = dbms->relations.find(Rname);
    //dbms->update_cmd(it->second, ) needs to be looked at
    return true;
}

bool Parser::insert_cmd(){
    int start = counter;

    if (tokens[counter].str != "INSERT"){
        counter = start;
        return false;
    }
    ++counter;

    if (tokens[counter].str != "INTO"){
        counter = start;
        return false;
    }
    ++counter;

    auto name = relation_name();
    if (!name) {
        counter = start;
        return false;
    }

    if (tokens[counter].str != "VALUES"){
        counter = start;
        return false;
    }
    ++counter;
    if (tokens[counter].str != "FROM"){
        counter = start;
        return false;
    }
    ++counter;


    if (tokens[counter].str == "RELATION") {
        ++counter;
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
        if (tokens[counter].str == "(") {
            ++counter;
            auto lit = literal();
            if (!lit){
                counter = start;
                return false;
            }
            vector<string> lits;
            lits.push_back(lit);
            while (true){
                int tempStart = counter;

                if (tokens[counter].str != ",") {
                    counter = tempStart;
                    break;
                }
                ++counter;
                lit = literal();
                if (!lit) {
                    counter = tempStart;
                    break;
                }
            }

            if (tokens[counter].str != ")"){
                counter = start;
                return false;
            }
            unordered_map<string, Table>::iterator it = dbms->relations.find(name);
            //dbms-> insert( it->second, something else);
            return true;

        }
        else{
            counter = start;
            return false;
        }
    }
}

bool Parser::delete_cmd(){
    int start = counter;

    if (tokens[counter].str != "DELETE"){
        counter = start;
        return false;
    }
    ++counter;
    if (tokens[counter].str != "FROM"){
        counter = start;
        return false;
    }
    ++counter;

    auto name = relation_name();
    if (!name){
        counter = start;
        return false;
    }

    if (tokens[counter].str != "WHERE"){
        counter = start;
        return false;
    }
    ++counter;

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
    while (true){
        int tempStart = counter;
        if (tokens[counter].str != ","){
            counter = tempStart;
            break;
        }
        ++counter;
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
    if (tokens[counter].str == "VARCHAR"){
        ++counter;
        if (tokens[counter].str != "(") {
            counter = start;
            return false;
        }
        ++counter;
        int integr = integer();
        if (!integr){
            counter = start;
            return false;
        }
        if (tokens[counter].str != ")") {
            counter = start;
            return false;
        }
        return Type(1, integr);
    }
    else if (tokens[counter].str == "INTEGER") {
        return Type(1, -1);
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

ParsedResult<Table> Parser::program(){
    int start = counter;

    auto qry = query();
    if (!qry){
        //auto cmmd = command();
        //if ( !cmmd ){
        //  counter = start;
        //  return false;
        //}
        //else{
        //
        //}
        return Table(); //just for now until command() is made
    }
    else return qry;
}

/////////////////// DMITRY /////////////////////////
ParsedResult<string> Parser::relation_name()
{
    int start = counter;

    auto result = identifier();
    if (!result)
    {
        counter = start;
        return false;
    }

    return result;
}



ParsedResult<Table> Parser::expr()
{
    int start = counter;

    // atomic expression, OR one of the following operations
    // check if atomic expression
    Table table;
    if (tokens[counter].str == "selection")
    {
        table = selection();
    }

    else if ( (tokens[counter].str == "project") ||
         (tokens[counter].str == "rename") )
    {
        table = project_AND_rename();
    }

    else if ( (tokens[counter].str == "union") ||
         (tokens[counter].str == "difference") ||
         (tokens[counter].str == "natural-join") ||
         (tokens[counter].str == "project") )
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



ParsedResult<Table> Parser::atomic_expr()
{
    int start = counter;

    Table table;
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

        auto table1 = expr();
        if (!table1)
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



ParsedResult<Table> Parser::selection()
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
    auto condition_result = condition();
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
    auto tableR = atomic_expr();
    if (!tableR)
    {
        counter = start;
        return false;
    }
    Condition* temp = condition_result;
    return dbms->selection(*temp, tableR);
}

ParsedResult<string>    Parser::attribute_name()
{
    int start = counter;

    if (counter >= tokens.size() || !isAlnum(tokens[counter]))
    {
        counter = start;
        return false;
    }

    return tokens[counter++].str;
}



ParsedResult<Table> Parser::project_AND_rename() /////////////////////////////////
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
    else    // not project OR rename
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



ParsedResult<vector<string>>    Parser::attribute_list()
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
    return vector<string>();
}


// Union, Diff, Projection, NaturalJoin
ParsedResult<Table> Parser::relational_algebra()
{
    // is next word a table name? or is it another expression
    int start = counter;

    // Takes Table OR expression
    // either result is a table
    Table table1;
    Table table2;

    // Read first atomic expr
    auto table1R = atomic_expr();
    if (!table1R)
    {
        counter = start;
        return false;
    }

    // Store operator for the operation
    string Op = tokens[counter].str;
    counter++;

    // Read second atomic expr
    auto table2R = atomic_expr();
    if (!table2R)
    {
        counter = start;
        return false;
    }

    switch  (Op[0])
    {
        case '+': return dbms->union_(table1, table2);
        case '-': return dbms->difference(table1, table2);
        case '*': return dbms->cross_product(table1, table2);
        case 'J': return dbms->natural_join(table1, table2);     // Join
        default:    return false;
    }
}

ParsedResult<string> Parser::identifier()
        {
    return "";
        }
ParsedResult<Table> Parser::query() {
    return Table();
}
