// Class Includes
#include "DBMS.h"
#include "Condition.h"
#include "Tokenizer.h"
#include "Parser.h"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;


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
using namespace std;

const string fileType = ".db";
const string VARCHAR = "VARCHAR";
const string INTEGER = "INTEGER";


Table DBMS::open_cmd(string name){
	//initialize some basic data
	ifstream file;
	file.open(name + fileType);
	if (!file.is_open()) return Table(); //could not open the file
	vector< vector<string> > rows;

	//get all the rows
	string line;
	int counter = 0;
	while (getline(file, line)) {
		rows.push_back(vector<string>());
		stringstream ss;
		ss << line;
		string word;
		while (ss >> word){
			rows[counter].push_back(word);
		}
		++counter;
	}

	//get the attributes and their types
	vector<pair<string, Type> > attributes;
	int size = rows[0].size();
	for (int i = 0; i < size; i += 2){
		string type = (rows[0])[i + 1];
		Type t;
		t.index = i / 2;
		if (type.substr(0, 7) == VARCHAR) {
			int j = VARCHAR.size() + 1;
			string c = "";
			while (type[j] != ')'){
				c += type[j];
				++j;
			}
			t.type = atoi(c.c_str());
		}
		else {
			t.type = -1;
		}
		pair<string, Type> temp((rows[0])[i], t);
		attributes.push_back(temp);
	}
	file.close();

	//create the table
	vector<string> tempToCompile;
	create_cmd(name, attributes, tempToCompile);
	//get a pointer to the table
	unordered_map<string, Table>::iterator it = relations.find(name);
	//insert all of the rows into the table
	for (int i = 1; i<rows.size(); ++i){
		insert_cmd(it->second, rows[i]);
	}

	return it->second;
}

void DBMS::close_cmd(string name){
	//initialize some basic data
	unordered_map<string, Table>::iterator it = relations.find(name);
	if (it == relations.end()) return; //could not find the relation
	ofstream file;
	file.open(name + fileType);
	if (!file.is_open()) return; //could not open the file

	//get the first line (attributes)
	vector<string> attributes;
	vector<int> sizes;
	Table* ptable = &(it->second);
	for (auto& attribute : ptable->attributeMap){
		attributes.push_back(attribute.first);
		int size = attribute.second.type;
		if (size == -1){
			attributes.push_back(INTEGER);
			sizes.push_back(15);
		}
		else{
			sizes.push_back(size);
			attributes.push_back(VARCHAR + "(" + to_string(size) + ")");
		}
	}

	//add to file
	int numOfColumns = sizes.size();
	for (int i = 0; i<numOfColumns * 2; i += 2){
		string temp = attributes[i] + " " + attributes[i + 1]+ " ";
		while (temp.size() <= sizes[i / 2]){
			temp += " ";
		}
		file << temp;
	}
	file << '\n';

	//add the rows to the file
	for (vector<string> row : ptable->rows){
		for (int i = 0; i<numOfColumns; ++i){
			string line = row[i];
			while (line.size() < sizes[i]) line += " ";
			file << line;
		}
		file << '\n';
	}
	file.close();
}

void DBMS::write_cmd(string name){
    ofstream file;
    file.open(name+fileType);
    file.close();
    close_cmd(name);
}

void DBMS::exit_cmd(){ exit(0);
    }


void DBMS::show_cmd(Table& table){
    //get the first line (attributes)
    vector<string> attributes;
    vector<int> sizes;
    for (auto& attribute : table.attributeMap){
        attributes.push_back(attribute.first);
        int size = attribute.second.type;
        if (size == -1){
            attributes.push_back(INTEGER);
            sizes.push_back(15);
        }
        else{
            sizes.push_back(size);
            attributes.push_back(VARCHAR + "(" + to_string(size) + ")");
        }
    }

    //write to screen
    int numOfColumns = sizes.size();
    for (int i = 0; i<numOfColumns * 2; i += 2){
        string temp = attributes[i] + " " + attributes[i + 1]+ " ";
        while (temp.size() < sizes[i / 2]){
            temp += " ";
        }
        cout << temp;
    }
    cout << '\n';

    //print the rows
    if (table.rows.size() == 0) cout << "NO DATA IN TABLE" << '\n';
    else{
        for (vector<string> row : table.rows){
            for (int i = 0; i < numOfColumns; ++i){
                string line = row[i];
                while (line.size() < sizes[i]) line += " ";
                cout << line;
            }
            cout << '\n';
        }
    }
}

/******************** Table Manipulation *******************************/
void DBMS::create_cmd(string name, vector< pair<string, Type> >& attributes, vector<string>& primaryKey)
{ // Lincoln
    Table table;
    int size = attributes.size();
    for (int i = 0; i < size; ++i) //go through each attribute and add it to the attribute map
        table.attributeMap.insert(attributes[i]);
    table.keys = primaryKey;
    relations[name] = table;
}

void DBMS::delete_cmd(string name)
{ // Shayan
    relations.erase(name);
}

void DBMS::delete_cmd(Table& table, Condition& cond)
{// Lincoln
    table.rows.remove_if([&table, &cond](const vector<string>& row) {
       return cond(row, table);
    });
}

void DBMS::update_cmd(Table& table, vector<pair<int, string>>& fieldsToUpdate, Condition& cond) // tuple<attributeName, Value>
{
    // Dmitry
    for(vector<string>& row : table.rows)
        if(cond(row, table))
            for(int i = 0; i < fieldsToUpdate.size(); ++i)
                row[fieldsToUpdate[i].first] = fieldsToUpdate[i].second;
}


void DBMS::insert_cmd(Table& table, vector<string> values)
{
    // Shayan
    if(values.size() != table.attributeMap.size())
        throw "Not enough attributes were given.";

    table.rows.push_back(vector<string>(table.attributeMap.size()));
    for(auto& pair : table.attributeMap)
    {
        Type& t = pair.second; // pair<name, (index, type)>

        // Type checking:
        if(t.type == -1)
            try { stringToInt(values[t.index]); }
            catch (...)
            {
                table.rows.pop_back();
                throw "Wrong type: " + values[t.index];
            }

        table.rows.back()[t.index] = values[t.index]; // The actual assignment
    }

    // If it's a duplicate, pop it out!
    if(find_if(table.rows.begin(), --table.rows.end(),
        [&table, &values](const vector<string>& row)
        {
        //  Are there any other rows with the exact same primary key values as the newly added row?
            for(string s : table.keys)
            {
                int index = table.attributeMap[s].index;
                if(row[index] != values[index])
                    return false;
            }
            return true;
        }) != --table.rows.end()) // --rows.end() to exclude the newly added element
        table.rows.pop_back();
    // endif
}

void DBMS::insert_cmd(Table& table, const Table& fromRelation)
{
    // Shayan
    if(!is_union_compatible(table, fromRelation))
        throw "Not union compatible.";

    for(auto& row : fromRelation.rows)
        insert_cmd(table, row);
}

// Shayan
list<vector<string>> DBMS::execute(string input)
{
    ParsedResult<Table> result(false);
    try
    {
        result = Parser(Tokenizer::tokenize(input), this).program();
    }
    catch (const char* c)
    {
        cout << "!!!ERROR!!!" << endl;;
        cout << c << endl;
    }
    if(!result) return list<vector<string>>();
    return ((Table)result).rows;
}

// Shayan
bool is_union_compatible(const Table& t1, const Table& t2)
{
    if(t1.attributeMap.size() != t2.attributeMap.size())
        return false;

    for(auto& pair1 : t1.attributeMap) // pair<name, Type>
    {
        auto pair2 = t2.attributeMap.find(pair1.first);

        // Has attribute with the same name?
        if(pair2 == t2.attributeMap.end())
            return false;

        // Same place?
        if(pair2->second.index != pair1.second.index)
            return false;

        // Same type? int == -1, so negative means different types
        if(pair2->second.type * pair1.second.type < 0)
            return false;
    }

    return true;
}



/******************** Table Logic Algebra *******************************/
Table DBMS::selection(Condition& cond, const Table& table)
{// Lincoln
    Table selected;
    selected.attributeMap = table.attributeMap;
    for (auto it = table.rows.begin(); it != table.rows.end(); ++it){ //go through each row
        if (cond(*it, table)) selected.rows.push_back(*it);  //if the row passes the condition add it to the new table
    }
    return selected;
}



Table DBMS::projection(vector<string>& attributes, const Table& table)
{// Lincoln
    Table proj;
    int numOfAtts = attributes.size();
    int numOfRows = table.rows.size();
    list<vector<string> > lines;    //hold the rows for the project for now
    for (int i = 0; i < numOfRows; ++i){//set up all the rows for the projection, but leave them empty for now
        vector<string> temp;
        lines.push_back(temp);
    }
    for (int i = 0; i < numOfAtts; ++i){    //go through all the wanted attributes
        auto it = table.attributeMap.find(attributes[i]); //get an iterator to the Type of the attribute
        auto itA = lines.begin(); //iterator to the row where the attribute needs to be inserted
        auto itB = table.rows.begin(); //iterator to the attribute that needs to be inserted into new table
        for (int j = 0; j < numOfRows; ++j){    //go through every row
            itA->push_back((*itB)[(it->second).index]); //add the correct string, based on the types index, from the old table to the projection
            ++itA;  //go to next line for the projection
            ++itB;  //go to next line for the old table
        }
        Type temp = it->second;
        temp.index = i; //change the index of the type to the new index
        proj.attributeMap[attributes[i]] = temp; //add the attribute to the projection

    }
    proj.rows = lines;  //add all of the rows to the project
    return proj;
}


Table DBMS::renaming(vector<string>& attributes, const Table& table)
{
    // Shayan
    Table renamed;
    renamed.rows = table.rows;

    if(attributes.size() != table.attributeMap.size())
        throw "Not enough attributes were given.";
    for(auto& pair : table.attributeMap)
    {
        const Type& t = pair.second; // pair<name, (index, type)>
        if(renamed.attributeMap.find(attributes[t.index]) != renamed.attributeMap.end())
            throw "Repeated attribute name.";

        renamed.attributeMap[attributes[t.index]] = t;
    }

    return renamed;
}


Table DBMS::union_(const Table& t1, const Table& t2)
{
    // Dmitry

    // Make new copies of table, to manipulate then display
    Table table1 = t1;
    Table table2 = t2;

    // Does table1 & table2 have same number of attributs?
    if (table1.attributeMap.size() != table2.attributeMap.size())
    {
        throw "Error! Not union compatible";
    }

    // Do both have the same type of attributes?
    string name;
    for (auto & t : table1.attributeMap)
    {
        if (table2.attributeMap.find(t.first) == table2.attributeMap.end())
        {
            throw "Attributes do not match";
        }
    }

    // Do the attributes index match for table1 & table2?
    Type type;

    // Search through table1 attributeMap
    for (auto & t : table1.attributeMap)
    {
        // If table2.attributeMap index != t.attributeMap index
        if ( table2.attributeMap.find(t.first)->second.index != t.second.index )
        {
            // Re-assign table2.attributeMap type, or give it temp value
            type = table2.attributeMap.find(t.first)->second;

            // move attrb values to corresponding indx to table1
            for(vector<string> row : table2.rows)
            {
                // move value from current to aligned with table1
                row.insert(row.begin() + t.second.index, row[type.index]);
                row.erase(row.begin() + type.index);
            }

            // Current table2 attribute map index = table1 attribute index, now are same indx
            table2.attributeMap.find(t.first)->second.index = t.second.index;
        }
    }


    bool duplicate = true;
    // Union the tables, while checking for duplicates
    for(vector<string> row1 : table1.rows)  // check table1
    {
        for(vector<string> row2 : table2.rows) // with all of table2 entries
        {
            for (int j = 0; j < row2.size(); j++)
            {
                if ( row1[j] != row2[j])
                    duplicate = false;
            }
        }

        // No duplicate found, copy table1[0] into table2.front
        if (duplicate == false)
        {
            table2.rows.push_front(row1);
        }

        // Reset duplicate
        duplicate = true;
    }
    return table2;
}



Table DBMS::difference(const Table& t1, const Table& t2)
{
    // Dmitry

    Table table1 = t1;
    Table table2 = t1;

    // Does t1 & t2 have same number of attributs?
    if (table1.attributeMap.size() != table2.attributeMap.size())
    {
        throw "Not union Compatible";
    }

    // Do both have the same type of attributes?
    string name;
    for (auto & t : table1.attributeMap)
    {
        if (table2.attributeMap.find(t.first) == table2.attributeMap.end())
        {
            throw "Attributes do not match";
        }
    }

    // Do the attributes index/location match for table1 & table2?
    Type type;
    // iterate through every attribute index
    for (auto & map1 : table1.attributeMap)
    {
        // If table2.attributeMap index != t.attributeMap index
        if ( table2.attributeMap.find(map1.first)->second.index != map1.second.index )
        {
            // Re-assign table2.attributeMap type, or give it temp value
            type = table2.attributeMap.find(map1.first)->second;

            // move attrb values to corresponding indx to table1
            for(vector<string> row2 : table2.rows)
            {
                // move value from current to aligned with table1
                row2.insert(row2.begin() + map1.second.index, row2[type.index]);
                row2.erase(row2.begin() + type.index);
            }

            // Current table2 attribute map index = table1 attribute index, now are same indx
            table2.attributeMap.find(map1.first)->second.index = map1.second.index;
        }
    }
    // Both tables have same order of attribute types

    // Copy current table1, clean its list, use to fill final table to return
    Table difference = table1;
    table1.rows.erase(table1.rows.begin(), table1.rows.end());

    bool duplicate = false;
    // Subtract
    for(vector<string> row1 : table1.rows)  // check table1
    {
        for(vector<string> row2 : table2.rows) // with all of table2 entries
        {
            for (int i = 0; i < row2.size(); i++)
            {
                // if copy of rows, do not add to new table
                if ( row1[i] == row2[i] )
                {
                    duplicate = true;
                }
            }

        }

        if (!duplicate)
        {
            difference.rows.push_back(row1);
        }

        // Reset duplicate
        duplicate = false;
    }
        return difference;

}


Table DBMS::cross_product(const Table& t1, const Table& t2)
{
    // Shayan
    Table xprod;

    // Merging the attributeMaps:
    xprod.attributeMap = t1.attributeMap;
    for(auto pair : t2.attributeMap) // pair<name, (index, type)
    {
        pair.second.index += t1.attributeMap.size();
        xprod.attributeMap["_" + pair.first] = pair.second; // Hyphenated to avoid repeated names
    }

    // Creating the cross-producted rows:
    for(auto& row1 : t1.rows)
        for(auto& row2 : t2.rows)
        {
            xprod.rows.push_back(row1); // TODO Consider making it faster by .reserve() beforehand.
            xprod.rows.back().insert(xprod.rows.back().end(), row2.begin(), row2.end());
        }

    return xprod;
}

Table DBMS::natural_join(const Table& t1, const Table& t2)
{
    
    // Dmitrys
    Table table1 = t1;
    Table table2 = t2;

    // create new_index list to hold where table1 attributes will go in table2
    unordered_map<string, int> new_index;   
    vector<string> similar_attrb;
    int indx_temp = 0;
    string attrb_temp_name;

    // find max index size sin table2
    int max2 = 0;
    for(auto& map2 : table2.attributeMap)
    {
        if (max2 < map2.second.index)
        {
            max2 = map2.second.index;
        }
    }

    int i = 1;
    for (auto& map1 : table1.attributeMap)  // check table1 
    {

        // Hold attrb name in temp string
        attrb_temp_name = table2.attributeMap.find(map1.first)->first;

        // Similar Attribute
        if (table2.attributeMap.find(map1.first) != table2.attributeMap.end())
        {
            // give a new_indesx to table1's attrb value, so that it will match
            // into table2 attrb column
            indx_temp = table2.attributeMap.find(map1.first)->second.index;

            // Pair current name and its new index together
            pair<string, int> temp(attrb_temp_name, indx_temp);
            new_index.insert(temp);
        }
        
        // Not Similar Attribute
        else
        {
            // new index = map2 + counter. This will be a new attrb column
            // in table2, hence it needs new proper index.
            indx_temp = max2 + i;

            // Pair current name and its new index together
            pair<string, int> temp(attrb_temp_name, indx_temp);
            new_index.insert(temp);
            
            i++;        
        }
    }
    


    bool param_same = true;
    // Iterate through all the rows in table1
    for(auto& rows1 : table1.rows)
    {
        // Compare rows[i] to all rows in t2
        for(auto& rows2 : t2.rows)
        {
            for (int i = 0; i < rows2.size(); i++)
            {
				/*
                // if values match, continue
                if (rows2[i] == new_index.find(rows2[i])->second)
                {
                    
                }

                // if values don't exist/match, append to column
                else
                {

                }
				*/
            }
        }
    }


    return t2;
}
