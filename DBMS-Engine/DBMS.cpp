// Class Includes
#include "DBMS.h"


using namespace std;

Table DBMS::open_cmd(string name){
    //initialize some basic data
    fstream file;
    file.open(name+fileType);
    if( ! file.is_open() ) return Table(); //could not open the file
    vector< vector<string> > rows;
    
    //get all the rows
    string line;
    int counter = 0;
    while ( getline(file, line) ) {
        rows.push_back(vector<string>());
        stringstream ss;
        ss << line;
        string word;
        while ( ss >> word ){
            rows[counter].push_back(word);
        }
        ++counter;
    }
    
    //get the attributes and their types
    vector<pair<string, Type> > attributes;
    int size = rows[0].size();
    for(int i=0; i < size; i += 2){
        string type = (rows[0])[i+1];
        Type t;
        t.index = i/2;
        if( type.substr(0,7) == VARCHAR ) {
            int j = VARCHAR.size() + 1;
            string c = "";
            while( type[j] != ')' ){
                c += type[j];
            }
            t.type = atoi(c.c_str());
        }
        else {
            t.type = -1;
        }
        pair<string, Type> temp( (rows[0])[i] , t );
        attributes.push_back( temp );
        file.close();
    }
    
    //create the table
    create_cmd(name, attributes, vector<string>());
    //get a pointer to it
    unordered_map<string,Table>::iterator it = relations.find(name);
    //insert all of the rows into the table
    for(int i=1; i<rows.size(); ++i){
        insert_cmd( it->second, rows[i] );
    }

    return it->second;
}

void DBMS::close_cmd(string name){
    //initialize some basic data
    unordered_map<string,Table>::iterator it = relations.find(name);
    if( it == relations.end() ) return; //could not find the relation
    ofstream file;
    file.open(name+fileType);
    if( ! file.is_open() ) return; //could not open the file

    //get the first line (attributes)
    vector<string> attributes;
    vector<int> sizes;
    Table* ptable = &(it->second);
    for(auto& attribute : ptable->attributeMap ){
        attributes.push_back(attribute.first);
        int size = attribute.second.type;
        if(size == -1){
            attributes.push_back(INTEGER);
            sizes.push_back(15);
        }
        else{
            char s[sizeof(int)];
            itoa(size,s,10);
            attributes.push_back(VARCHAR+"("+ s + ")");
            sizes.push_back(size+10);
        }
    }
    
    //add to file
    int numOfColumns = sizes.size();
    for(int i=0; i<numOfColumns*2; i+=2){
        string temp = attributes[i] + " " + attributes[i+1];
        while(temp.size() <= sizes[i]){
            temp += " ";
        }
        file << temp;
    }
    file << '\n';

    //add the rows to the file
    for(vector<string> row : ptable->rows){
        for(int i=0; i<numOfColumns; ++i){
            string line = row[i];
            while(line.size() < sizes[i]) line += " ";
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

void DBMS::exit_cmd(){ ~DBMS(); }

void DBMS::show_cmd(Table table){
    //initialize some basic data
    unordered_map<string,Table>* it = &(table);

    //get the first line (attributes)
    vector<string> attributes;
    vector<int> sizes;
    Table* ptable = &(it->second);
    for(auto& attribute : ptable->attributeMap ){
        attributes.push_back(attribute.first);
        int size = attribute.second.type;
        if(size == -1){
            attributes.push_back(INTEGER);
            sizes.push_back(15);
        }
        else{
            char s[sizeof(int)];
            itoa(size,s,10);
            attributes.push_back(VARCHAR+"("+ s + ")");
            sizes.push_back(size+10);
        }
    }

    //write to screen
    int numOfColumns = sizes.size();
    for(int i=0; i<numOfColumns*2; i+=2){
        string temp = attributes[i] + " " + attributes[i+1];
        while(temp.size() <= sizes[i]){
            temp += " ";
        }
        cout << temp;
    }
    cout << '\n';

    //print the rows
    for(vector<string> row : ptable->rows){
        for(int i=0; i<numOfColumns; ++i){
            string line = row[i];
            while(line.size() < sizes[i]) line += " ";
            cout << line;
        }
        cout << '\n';
    }
}
