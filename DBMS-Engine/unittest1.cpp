#include "stdafx.h"
#include "CppUnitTest.h"
#include "DBMS.h"
#include "Parser.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::ifstream;
using std::stringstream;

namespace DBMStest
{
	TEST_CLASS(DBMStest)
	{
		DBMS database;
		Table table;
		string name = "numbers";
		vector<pair<string, Type>> attributes;
		vector<string> keys;
		list<vector<string>> rows;
		TEST_METHOD_INITIALIZE(DBMSinitializing){
			attributes.push_back(pair<string, Type>("name", Type(0, 15)));
			attributes.push_back(pair<string, Type>("value", Type(1, -1)));
			keys.push_back("value");
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
			table.rows = rows;
			table.keys = keys;
			table.attributeMap.insert(pair<string, Type>("name", Type(0, 15)));
			table.attributeMap.insert(pair<string, Type>("value", Type(1, -1)));
			database.relations.insert(pair<string, Table>(name, table));
			database.write_cmd("numbers.db");
		};

		TEST_METHOD_CLEANUP(DBMScleaning){

		};
	public:
		
		TEST_METHOD(DBMScreate_cmd)
		{
			database.create_cmd(name, attributes, keys);
			auto it = database.relations.find(name);
			auto itA = it->second.attributeMap.find("name");
			auto itB = it->second.attributeMap.find("value");

			Assert::IsTrue((it->first == name) &&
				(it->second.keys[0] == keys[0]) &&
				(itA->second.type == 15) &&
				(itB->second.index == 1));
		}

		TEST_METHOD(DBMSproject)
		{
			vector<string> projAtts;
			projAtts.push_back("value");

			Table proj = database.projection(projAtts, table);
			vector<string> tester = proj.rows.front();

			Assert::IsTrue((proj != table) &&
				(tester[0] == "0"));
		}
	
		TEST_METHOD(DBMSwrite_cmd){
			remove("numbers.db");
			database.write_cmd(name);
			ifstream file;
			file.open("numbers.db");
			string test;

			Assert::IsTrue(file.is_open() &&
				(file >> test) &&
				(test == "name"));
		}
	
		TEST_METHOD(DBMSclose_cmd){
			auto it = database.relations.find(name);
			vector<string> row3;
			row3.push_back("three");
			row3.push_back("3");
			database.insert_cmd(it->second, row3);
			database.close_cmd(name);

			ifstream file;
			file.open("numbers.db");
			string test;

			vector<vector<string>> testerRows;
			string line;
			int counter = 0;
			while (getline(file, line)) {
				testerRows.push_back(vector<string>());
				stringstream ss;
				ss << line;
				string word;
				while (ss >> word){
					testerRows[counter].push_back(word);
				}
				++counter;
			}

			Assert::IsTrue(file.is_open() &&
				( (testerRows[testerRows.size()-1])[0] == "three") );
		}
	
		TEST_METHOD(DBMSopen_cmd){
			database.relations.erase(name);

			Table tester = database.open_cmd(name);
			auto it = database.relations.find(name);
			ifstream file;
			file.open(name + ".db");

			Assert::IsTrue(file.is_open() &&
				(it->first == name) );

		}
		
		TEST_METHOD(DBMSdelete_cmd){
			auto it = database.relations.find(name);
			vector<Token> tokens;
			tokens.push_back("value");
			tokens.push_back(">");
			tokens.push_back("1");
			Parser parser(tokens, &database);
			Condition* pntr = parser.condition();

			
			database.delete_cmd(it->second, *pntr);

			Assert::IsTrue(false);
		}
		//^^not working (condition pointer)
		TEST_METHOD(DBMSselection_cmd){
			Assert::IsTrue(false);
		}
		//^^not working (condition pointer)
	};
}

namespace PARSERTest{
	TEST_CLASS(PARSERTest)
	{
		DBMS database;
		Table table;
		string name = "numbers";
		vector<pair<string, Type>> attributes;
		vector<string> keys;
		list<vector<string>> rows;
		vector<Token> tokens;
		TEST_METHOD_INITIALIZE(PARSERinitializing){
			attributes.push_back(pair<string, Type>("name", Type(0, 15)));
			attributes.push_back(pair<string, Type>("value", Type(1, -1)));
			keys.push_back("value");
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
			table.rows = rows;
			table.keys = keys;
			table.attributeMap.insert(pair<string, Type>("name", Type(0, 15)));
			table.attributeMap.insert(pair<string, Type>("value", Type(1, -1)));
			database.relations.insert(pair<string, Table>(name, table));
			database.write_cmd("numbers.db");
		};

		TEST_METHOD_CLEANUP(PARSERcleaning){

		};

	public:
		TEST_METHOD(PARSERinteger){
			tokens.push_back("33");
			Parser parse(tokens, &database);

			Assert::IsTrue(parse.integer());
		}

		TEST_METHOD(PARSERtype){
			tokens.push_back("VARCHAR");
			tokens.push_back("(");
			tokens.push_back("15");
			tokens.push_back(")");
			Parser parse(tokens, &database);

			Assert::IsTrue(parse.type());
		}

		TEST_METHOD(PARSERtyped_attribute_list){
			tokens.push_back("color");
			tokens.push_back("VARCHAR");
			tokens.push_back("(");
			tokens.push_back("15");
			tokens.push_back(")");
			tokens.push_back(",");
			tokens.push_back("weight");
			tokens.push_back("INTEGER");
			Parser parse(tokens, &database);

			Assert::IsTrue(parse.typed_attribute_list());
		}

		TEST_METHOD(PARSERopen_cmd){
			tokens.push_back("OPEN");
			tokens.push_back("numbers");
			Parser parse(tokens, &database);

			Assert::IsTrue(parse.open_cmd());
		}

		TEST_METHOD(PARSERclose_cmd){
			tokens.push_back("CLOSE");
			tokens.push_back("numbers");
			Parser parse(tokens, &database);

			Assert::IsTrue(parse.close_cmd());
		}

		TEST_METHOD(PARSERwrite_cmd){
			tokens.push_back("WRITE");
			tokens.push_back("numbers");
			Parser parse(tokens, &database);

			Assert::IsTrue(parse.write_cmd());
		}

		TEST_METHOD(PARSERexit_cmd){
			tokens.push_back("EXIT");
			tokens.push_back("numbers");
			Parser parse(tokens, &database);

			Assert::IsTrue(parse.exit_cmd());
		}

		TEST_METHOD(PARSERshow_cmd){
			tokens.push_back("SHOW");
			tokens.push_back("numbers");
			Parser parse(tokens, &database);

			Assert::IsTrue(parse.show_cmd());
		}

		TEST_METHOD(PARSERcreate_cmd){
			tokens.push_back("CREATE");
			tokens.push_back("TABLE");
			tokens.push_back("Colors");
			tokens.push_back("(");
			tokens.push_back("color");
			tokens.push_back("VARCHAR");
			tokens.push_back("(");
			tokens.push_back("15");
			tokens.push_back(")");
			tokens.push_back(",");
			tokens.push_back("weight");
			tokens.push_back("INTEGER");
			tokens.push_back(")");
			tokens.push_back("PRIMARY");
			tokens.push_back("KEY");
			tokens.push_back("(");
			tokens.push_back("color");
			tokens.push_back(")");

			Parser parse(tokens, &database);

			Assert::IsTrue(parse.create_cmd());
		}
		//^^ doesnt work beacuse of attribute list
		TEST_METHOD(PARSERupdate_cmd){
			tokens.push_back("UPDATE");
			tokens.push_back("numbers");
			tokens.push_back("SET");
			tokens.push_back("name");
			tokens.push_back("=");
			tokens.push_back("called");
			tokens.push_back("weight");
			tokens.push_back("=");
			tokens.push_back("power");
			tokens.push_back("WHERE");
			tokens.push_back("(");
			tokens.push_back("weight");
			tokens.push_back("==");
			tokens.push_back("10");
			tokens.push_back(")");

			Parser parse(tokens, &database);

			Assert::IsTrue(parse.update_cmd());
		}
		//^^figure out why not working (condition pointer)
		TEST_METHOD(PARSEinsert_cmd1){
			tokens.push_back("INSERT");
			tokens.push_back("INTO");
			tokens.push_back("numbers");
			tokens.push_back("VALUES");
			tokens.push_back("FROM");
			tokens.push_back("(");
			tokens.push_back("\"five\"");
			tokens.push_back(",");
			tokens.push_back("5");
			tokens.push_back(")");

			Parser parser(tokens, &database);

			Assert::IsTrue(parser.insert_cmd());
		}

		TEST_METHOD(PARSEinsert_cmd2){
			tokens.push_back("INSERT");
			tokens.push_back("INTO");
			tokens.push_back("numbers");
			tokens.push_back("VALUES");
			tokens.push_back("FROM");
			tokens.push_back("RELATION");
			tokens.push_back("select");
			tokens.push_back("(");
			tokens.push_back("kind");
			tokens.push_back("==");
			tokens.push_back("\"dog\"");
			tokens.push_back("animals");

			Parser parser(tokens, &database);

			Assert::IsTrue(parser.insert_cmd());
		}
		//^^^ doesnt work (condition pointer)
		TEST_METHOD(PARSEdelete_cmd){
			tokens.push_back("DELETE");
			tokens.push_back("FROM");
			tokens.push_back("numbers");
			tokens.push_back("WHERE");
			tokens.push_back("value");
			tokens.push_back(">");
			tokens.push_back("1");

			Parser parser(tokens, &database);

			Assert::IsTrue(parser.delete_cmd());
		}
		//^^^ doesnt work (condition pointer)
	};
}
