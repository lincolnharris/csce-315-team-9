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
                                        "planeModel    VARCHAR(20),"
                                        "PRIMARY KEY (passengerName,"
                                                     "planeModel);");

    dbms.execute("CREATE TABLE Owns (airlineName VARCHAR(20),"
                                    "planeModel  VARCHAR(20),"
                                    "PRIMARY KEY (airlineName,"
                                                 "planeModel);");
}

AirportDB::~AirportDB()
{
}

void AirportDB::newAirlineList(string name)
{
    dbms.execute("CREATE TABLE " + name + " (name VARCHAR(20),"
                                            "HQ   VARCHAR(10),"
                                            "PRIMARY KEY (name);");

    if(airlineLists.find(name) != airlineLists.end())
        throw "Duplicate list!";
    airlineLists.insert(name);
}

void AirportDB::newPassengerList(string name)
{
    dbms.execute("CREATE TABLE " + name + " (name        VARCHAR(20),"
                                            "age         INTEGER,"
                                            "baggage     INTEGER,"
                                            "destination VARCHAR(10),"
                                            "PRIMARY KEY (name);");

    if(passengerLists.find(name) != passengerLists.end())
        throw "Duplicate list!";
    passengerLists.insert(name);
}

void AirportDB::newPlaneList(string name)
{
    dbms.execute("CREATE TABLE " + name + " (model     VARCHAR(20),"
                                            "capacity  INTEGER,"
                                            "PRIMARY KEY (model);");

    if(planeLists.find(name) != planeLists.end())
        throw "Duplicate list!";
    planeLists.insert(name);
}

void AirportDB::addPlane(string model, int capacity, string list)
{
    if(planeLists.find(list) == planeLists.end())
        throw "List not found!";

    dbms.execute("INSERT INTO " + list + " VALUES FROM (\"" + model               + "\", "
                                                            + to_string(capacity) + ");");
}

void AirportDB::addPassenger(string name, int age, int baggage, string destination, string list)
{
    if(passengerLists.find(list) == passengerLists.end())
    throw "List not found!";

    dbms.execute("INSERT INTO " + list + " VALUES FROM (\"" + name               + "\", "
                                                            + to_string(age)     + ", "
                                                            + to_string(baggage) + ", "
                                                       "\"" + destination        + "\");");
}

void AirportDB::addAirline(string name, string HQ, string list)
{
    if(airlineLists.find(list) == airlineLists.end())
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
    if(passengerLists.find(list) == passengerLists.end())
            throw "List not found!";

    dbms.execute("DELETE FROM " + list + " WHERE name == \"" + name + "\";");
}

void AirportDB::removePlane(string model, string list)
{
    if(planeLists.find(list) == planeLists.end())
            throw "List not found!";

    dbms.execute("DELETE FROM " + list + " WHERE model == \"" + model + "\";");
}

void AirportDB::removeAirline(string name, string list)
{
    if(airlineLists.find(list) == airlineLists.end())
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
    if(     airlineLists.find(list)   != airlineLists.end()
         || passengerLists.find(list) != passengerLists.end()
         || planeLists.find(list)     != planeLists.end())
        dbms.execute("WRITE " + list + ";");
    else throw "List not found!";
}

void AirportDB::load(string list)
{
    if(     airlineLists.find(list)   == airlineLists.end()
         && passengerLists.find(list) == passengerLists.end()
         && planeLists.find(list)     == planeLists.end())
        dbms.execute("OPEN " + list + ";");
    else throw "List already exists!";
}

// Lincoln
void AirportDB::merge(string list1, string list2)
{
	if (airlineLists.find(list1) != airlineLists.end()
	        && airlineLists.find(list2) != airlineLists.end()){
		airlineLists.insert(list1 + "AND" + list2);
	}
	else if (passengerLists.find(list1) != passengerLists.end()
	        && passengerLists.find(list2) != passengerLists.end()){
		passengerLists.insert(list1 + "AND" + list2);
	}
	else if (planeLists.find(list1) != planeLists.end()
	        && planeLists.find(list2) != planeLists.end()){
		planeLists.insert(list1 + "AND" + list2);
	}
	else return;
	dbms.execute(list1 + "AND" + list2 + " <-" + list1 + " + " + list2 + ";");
}

void AirportDB::subtract(string list1, string list2)
{
	if (airlineLists.find(list1) != airlineLists.end()
	        && airlineLists.find(list2) != airlineLists.end()){
		airlineLists.insert(list1 + "MINUS" + list2);
	}
	else if (passengerLists.find(list1) != passengerLists.end()
        && passengerLists.find(list2) != passengerLists.end()){
		passengerLists.insert(list1 + "MINUS" + list2);
	}
    else if (planeLists.find(list1) != planeLists.end()
        && planeLists.find(list2) != planeLists.end()){
		planeLists.insert(list1 + "MINUS" + list2);
	}
	else return;
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
	dbms.execute("DELETE " + list + "WithoutHeavyBaggage");
	return data;
}

