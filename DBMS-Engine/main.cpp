#include "DBMS.h"
#include "Parser.h"
#include <iostream>
using namespace std;

int main() {
	DBMS database;
	string name = "numbers";
	vector<pair<string, Type>> attributes;
	attributes.push_back(pair<string, Type>("name", Type(0, 15)));
	attributes.push_back(pair<string, Type>("value", Type(1, -1)));
	vector<string> keys;
	keys.push_back("value");
	list<vector<string>> rows;
	vector<string> row0;
	row0.push_back("zero");
	row0.push_back("0");
	rows.push_back(row0);
	vector<string> row1;
	row1.push_back("one");
	row1.push_back("1");
	rows.push_back(row1);
	vector<string> row2;
	row2.push_back("two");
	row2.push_back("2");
	rows.push_back(row2);
	Table table;
	table.rows = rows;
	table.keys = keys;
	table.attributeMap.insert(pair<string, Type>("name", Type(0, 15)));
	table.attributeMap.insert(pair<string, Type>("value", Type(1, -1)));
	database.relations.insert(pair<string, Table>(name, table));

	database.write_cmd(name);
	database.relations.erase(name);
	database.open_cmd(name);
	auto it = database.relations.find(name);
	database.show_cmd(it->second);
	cout << "\n\n\n";

	vector<Token> tokens;
	tokens.push_back("color");
	tokens.push_back("VARCHAR");
	tokens.push_back("(");
	tokens.push_back("15");
	tokens.push_back(")");
	Parser parser(tokens, &database);
	parser.typed_attribute_list();

	string holdup;
	cin >> holdup;
	return 0;
}
