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
    if(!is_union_compatible(table, fromRelation))
        throw "Not union compatible.";

    // Just making sure they're the same; they could be different in attribute ordering.
    table.attributeMap = fromRelation.attributeMap;

    table.rows.insert(table.rows.end(), fromRelation.rows.begin(), fromRelation.rows.end());
}

/******************** Table Logic Algebra *******************************/
Table DBMS::selection(Comparison& cond, const Table& relation)
{
    // Lincoln
    return Table();
}


Table DBMS::projection(vector<string>& attributes, const Table& relation)
{
    // Lincoln
    return Table();
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


Table DBMS::union_(const Table& t1, const Table& t2)
{
    // Dmitry
    return Table();
}


Table DBMS::difference(const Table& t1, const Table& t2)
{
    // Dmitry
    return Table();
}

Table DBMS::cross_product(const Table& t1, const Table& t2)
{
    Table xprod;

    // Merging the attributeMaps:
    xprod.attributeMap.insert(t1.attributeMap.begin(), t1.attributeMap.end());
    for(auto pair : t2.attributeMap) // pair<name, (index, type)
    {
        pair.second.index += t1.attributeMap.size();
        xprod.attributeMap["_" + pair.first] = pair.second; // Hyphenated to avoid repeated names
    }

    // Creating the cross-producted rows:
    for(auto& row1 : t1.rows)
        for(auto& row2 : t2.rows)
        {
            xprod.rows.push_back(vector<string>());
            xprod.rows.back().insert(xprod.rows.back().end(), row1.begin(), row1.end());
            xprod.rows.back().insert(xprod.rows.back().end(), row2.begin(), row2.end());
        }

    return xprod;
}

Table DBMS::natural_join(const Table& t1, const Table& t2)
{
    // Dmitry
    return Table();
}

bool is_union_compatible(const Table& t1, const Table t2)
{
    if(t1.attributeMap.size() != t2.attributeMap.size())
        return false;

    // Do both have the same type of attributes?
    string name;
    for(auto& pair : t1.attributeMap) // pair<name, Type>
        if(t2.attributeMap.find(pair.first) == t2.attributeMap.end())
            return false;

    return true;
}
