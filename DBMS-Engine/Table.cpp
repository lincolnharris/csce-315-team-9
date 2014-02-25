/*
 * Table.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: Synix
 */

#include "Table.h"


Table::Table()
{
    // TODO Auto-generated constructor stub

}


Table::~Table()
{
    // TODO Auto-generated destructor stub
}

bool Table::operator==(const Table& t)
{
    if(attributeMap.size() != t.attributeMap.size() || rows.size() != t.rows.size())
        return false;
    for(auto& pair : t.attributeMap)
    {
        auto iterator = attributeMap.find(pair.first);
        if(iterator == attributeMap.end()) return false;
        if(iterator->first != pair.first || iterator->second != pair.second)
            return false;
    }
    auto it1 = rows.begin();
    auto it2 = t.rows.begin();
    while(it1 != rows.end())
    if(*(it1++) != *(it2++))
        return false;

    return true;
}

bool Table::operator!=(const Table& t)
{
    return !((*this) == t);
}



