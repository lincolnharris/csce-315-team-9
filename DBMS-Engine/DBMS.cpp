// Class Includes
#include "DBMS.h"
#include "Comparison.h"

/******************** Constructor / Destructor *******************************/
DBMS::DBMS()
{
    // Nothing
}

DBMS::~DBMS()
{
    // Nothing
}

/******************** DBMS General Commands *******************************/
//Table DBMS::open_cmd(string name)
//{
//
//
//}
//
//
//void DBMS::close_cmd(string name)
//{
//
//
//}
//
//
//void DBMS::write_cmd(string name)
//{
//
//
//}
//
//
//void DBMS::exit_cmd()
//{
//
//
//}
//
//
//void DBMS::show_cmd(string name)
//{
//
//
//}
//
/******************** Table Manipulation *******************************/
void DBMS::create_cmd(string name, vector<Type>& attributes, vector<string>& primaryKey)
{
    // Lincoln
}

void DBMS::delete_cmd(Table& table, Comparison& cond)
{
    // Lincoln
}

void DBMS::update_cmd(Table& table, vector<pair<int, string>>& fieldsToUpdate,
        Comparison& cond) // tuple<attributeName, Value>
{
    // Dmitry
}

void DBMS::insert_cmd(Table& table, vector<string>& values)
{
    table.rows.push_back(vector<string>(table.attributeMap.size()));

    if(values.size() != table.attributeMap.size())
        throw "Not enough attributes were given.";
    for(auto& pair : table.attributeMap)
    {
        Type& t = pair.second; // pair<name, (index, type)>

        // Type checking:
        if(t.type == -1)
            try { stoi(values[t.index]); }
            catch (...)
            {
                table.rows.pop_back();
                throw "Wrong type: " + values[t.index];
            }

        table.rows.back()[t.index] = values[t.index]; // The actual assignment
    }
}

void DBMS::insert_cmd(Table& table, const Table& fromRelation)
{
    // Shayan
}

/******************** Table Logic Algebra *******************************/
Table DBMS::selection(Comparison& cond, const Table& relation)
{
    // Lincoln
}


Table DBMS::projection(vector<string>& attributes, const Table& relation)
{
    // Lincoln
}


Table DBMS::renaming(vector<string>& attributes, const Table& table)
{
    unordered_map<string, Type> newAttributes;

    if(attributes.size() != table.attributeMap.size())
        throw "Not enough attributes were given.";
    for(auto& pair : table.attributeMap)
    {
        const Type& t = pair.second; // pair<name, (index, type)>
        if(newAttributes.find(attributes[t.index]) != newAttributes.end())
            throw "Repeated attribute name.";

        newAttributes[attributes[t.index]] = t;
    }
    // TODO what to return? does rename create a new table?
}


Table DBMS::union_(const Table& rel1, const Table& rel2)
{
    // Dmitry
}


Table DBMS::difference(const Table& rel1, const Table& rel2)
{
    // Dmitry
}

Table DBMS::cross_product(const Table& rel1, const Table& rel2)
{
    // Shayan
}

Table DBMS::natural_join(const Table& rel1, const Table& rel2)
{
    // Dmitry
}

