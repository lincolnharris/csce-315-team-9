/*
* Airport_Database.cpp
*
*  Created on: Feb 23, 2014
*      Author: Synix
*/
#include "AirportDB.h"
#include <sstream>

using namespace std;


// Shayan
AirportDB::AirportDB()
{
    dbms.execute("CREATE TABLE Boarding (passengerName VARCHAR(20),"
                                        "planeModel    VARCHAR(20))"
                                        "PRIMARY KEY (passengerName,"
                                                     "planeModel);");
	lists.insert("Boarding");
    dbms.execute("CREATE TABLE Owns (airlineName VARCHAR(20),"
                                    "planeModel  VARCHAR(20))"
                                    "PRIMARY KEY (airlineName,"
                                                 "planeModel);");
	lists.insert("Owns");
}

AirportDB::~AirportDB()
{
}

void AirportDB::newAirlineList(string name)
{
    dbms.execute("CREATE TABLE " + name + " (name VARCHAR(20),"
                                            "HQ   VARCHAR(10))"
                                            "PRIMARY KEY (name);");

    if(lists.find(name) != lists.end())
        throw "Duplicate list!";
    lists.insert(name);
}

void AirportDB::newPassengerList(string name)
{
    dbms.execute("CREATE TABLE " + name + " (name        VARCHAR(20),"
                                            "age         INTEGER,"
                                            "baggage     INTEGER,"
                                            "destination VARCHAR(10))"
                                            "PRIMARY KEY (name);");

    if(lists.find(name) != lists.end())
        throw "Duplicate list!";
    lists.insert(name);
}

void AirportDB::newPlaneList(string name)
{
    dbms.execute("CREATE TABLE " + name + " (model     VARCHAR(20),"
                                            "capacity  INTEGER)"
                                            "PRIMARY KEY (model);");

    if(lists.find(name) != lists.end())
        throw "Duplicate list!";
    lists.insert(name);
}

void AirportDB::addPlane(string model, int capacity, string list)
{
    if(lists.find(list) == lists.end())
        throw "List not found!";

    dbms.execute("INSERT INTO " + list + " VALUES FROM (\"" + model               + "\", "
                                                            + to_string(capacity) + ");");
}

void AirportDB::addPassenger(string name, int age, int baggage, string destination, string list)
{
    if(lists.find(list) == lists.end())
    throw "List not found!";

    dbms.execute("INSERT INTO " + list + " VALUES FROM (\"" + name               + "\", "
                                                            + to_string(age)     + ", "
                                                            + to_string(baggage) + ", "
                                                       "\"" + destination        + "\");");
}

void AirportDB::addAirline(string name, string HQ, string list)
{
    if(lists.find(list) == lists.end())
            throw "List not found!";

    dbms.execute("INSERT INTO " + list + " VALUES FROM (\"" + name + "\", "
                                                       "\"" + HQ   + "\");");
}

void AirportDB::board(string passengerName, string planeModel)
{
    dbms.execute("INSERT INTO Boarding VALUES FROM (\"" + passengerName + "\", "
                                                   "\"" + planeModel    + "\");");
}

void AirportDB::own(string airlineName, string planeModel)
{
    dbms.execute("INSERT INTO Owns VALUES FROM (\"" + airlineName + "\", "
                                               "\"" + planeModel  + "\");");
}

void AirportDB::removePassenger(string name, string list)
{
    if(lists.find(list) == lists.end())
            throw "List not found!";

    dbms.execute("DELETE FROM " + list + " WHERE name == \"" + name + "\";");
}

void AirportDB::removePlane(string model, string list)
{
    if(lists.find(list) == lists.end())
            throw "List not found!";

    dbms.execute("DELETE FROM " + list + " WHERE model == \"" + model + "\";");
}

void AirportDB::removeAirline(string name, string list)
{
    if(lists.find(list) == lists.end())
            throw "List not found!";

    dbms.execute("DELETE FROM " + list + " WHERE name == \"" + name + "\";");
}

void AirportDB::disembark(string passengerName, string planeModel)
{
    dbms.execute("DELETE FROM Boarding WHERE passengerName == \"" + passengerName + '"'
                                       + "&& planeModel    == \"" + planeModel    + "\";");
}

void AirportDB::disown(string airlineName, string planeModel)
{
    dbms.execute("DELETE FROM Boarding WHERE airlineName == \"" + airlineName + '"'
                                       + "&& planeModel  == \"" + planeModel  + "\";");
}

void AirportDB::updatePassenger(string name, string list, int updatedBaggage)
{
    dbms.execute("UPDATE " + list + " SET baggage = " + to_string(updatedBaggage)
                                  + " WHERE name == \"" + name + "\";");
}

void AirportDB::updateAirline(string name, string list, string newHQ)
{
    dbms.execute("UPDATE " + list + " SET baggage = \"" + name  + '"'
                                  + " WHERE name == \"" + newHQ + "\";");
}

void AirportDB::save(string list)
{
    if(lists.find(list)   != lists.end())
        dbms.execute("WRITE " + list + ";");
    else throw "List not found!";
}

void AirportDB::load(string list)
{
    if(lists.find(list)   == lists.end())
        dbms.execute("OPEN " + list + ";");
    else throw "List already exists!";
    lists.insert(list);
}

void AirportDB::show(string list)
{
    if(lists.find(list)   != lists.end())
        dbms.execute("SHOW " + list + ";");
    else throw "List not found!";
}

// Lincoln
void AirportDB::merge(string list1, string list2)
{
	if (lists.find(list1) != lists.end()
	        && lists.find(list2) != lists.end()){
		lists.insert(list1 + "AND" + list2);
	}
	else throw "Cannot merge!";
	dbms.execute(list1 + "AND" + list2 + " <-" + list1 + " + " + list2 + ";");
}

void AirportDB::natural_join(string list1, string list2)
{
	if (lists.find(list1) != lists.end()
		&& lists.find(list2) != lists.end()){
		lists.insert(list1 + "JOIN" + list2);
	}
	else throw "Cannot JOIN!";
	dbms.execute(list1 + "JOIN" + list2 + " <-" + list1 + " JOIN " + list2 + ";");
}

void AirportDB::subtract(string list1, string list2)
{
	if (lists.find(list1) != lists.end()
	        && lists.find(list2) != lists.end()){
		lists.insert(list1 + "MINUS" + list2);
	}
	else throw "Cannot merge!";
	dbms.execute(list1 + "MINUS" + list2 + "<-" + list1 + " - " + list2 + ";");
}

vector<string> AirportDB::listPassengerNames(string list)
{
    // Store the result in some temporary table
	auto data = dbms.execute(list + "PASSENGERS" + " <- project (name) " + list + ";");

	// Delete the temporary table
	dbms.execute("DELETE " + list + "PASSENGERS;");

	vector<string> names;
	for(vector<string>& row : data)
	    names.push_back(row[0]);

	return names;
}

list<vector<string>> AirportDB::filterHeavyBaggage(string list, int baggageLimit)
{
	string baggageMax = to_string(baggageLimit);
	auto data = dbms.execute(list + "WithoutHeavyBaggage <- select (baggage < " + baggageMax + ") " + list + ";");
    dbms.execute("DELETE " + list + "WithoutHeavyBaggage;");
	return data;
}

