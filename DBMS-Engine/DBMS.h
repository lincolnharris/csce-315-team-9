// Primary Include
#pragma once

// Default Include
#include <string>
#include <unordered_map>


// Class Includes
class Table;


using namespace std;

class DBMS
{

	private:

		unordered_map<string, Table> relations; 	// Constructor....

	public:

		DBMS();
		~DBMS();

		void Insert_Table();
		void Delete_Table();

		void Insert_Into();
		void Update();
		void Delete_From();

		void Selection();
		void Projection();
		void Renaming();
		void Union();
		void Difference();
		void Cross_Product();
		void Natural_Join();


};
