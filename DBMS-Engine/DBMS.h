// Primary Include
#ifndef DBMS_H          
#define DBMS_H

// Default Include
#include <string>


// Class Includes
class Table;


using namespace std;

class DBMS
{

	private:

		_unordered_map< string, Table > Table_Map; 	// Constructor....

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




# endif