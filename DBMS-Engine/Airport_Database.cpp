/*
* Airport_Database.cpp
*
*  Created on: Feb 23, 2014
*      Author: Synix
*/
#include "Airport_Database.h"

using namespace std;


Airport_Database::Airport_Database()
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

Airport_Database::~Airport_Database()
{
}

void Airport_Database::newAirlineList(string name)
{
    dbms.execute("CREATE TABLE " + name + " (name VARCHAR(20),"
                                            "HQ   VARCHAR(10),"
                                            "PRIMARY KEY (name);");

    if(airlineLists.find(name) != airlineLists.end())
        throw "Duplicate list!";
    airlineLists.insert(name);
}

void Airport_Database::newPassengerList(string name)
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

void Airport_Database::newPlaneList(string name)
{
    dbms.execute("CREATE TABLE " + name + " (model     VARCHAR(20),"
                                            "capacity  INTEGER,"
                                            "PRIMARY KEY (model);");

    if(planeLists.find(name) != planeLists.end())
        throw "Duplicate list!";
    planeLists.insert(name);
}

void Airport_Database::addPlane(string model, int capacity, string list)
{
    if(planeLists.find(list) == planeLists.end())
        throw "List not found!";

    dbms.execute("INSERT INTO " + list + " VALUES FROM (\"" + model               + "\", "
                                                            + to_string(capacity) + ");");
}

void Airport_Database::addPassenger(string name, int age, int baggage, string destination, string list)
{
    if(passengerLists.find(list) == passengerLists.end())
    throw "List not found!";

    dbms.execute("INSERT INTO " + list + " VALUES FROM (\"" + name               + "\", "
                                                            + to_string(age)     + ", "
                                                            + to_string(baggage) + ", "
                                                       "\"" + destination        + "\");");
}

void Airport_Database::addAirline(string name, string HQ, string list)
{
    if(airlineLists.find(list) == airlineLists.end())
            throw "List not found!";

    dbms.execute("INSERT INTO " + list + " VALUES FROM (\"" + name + "\", "
                                                       "\"" + HQ   + "\");");
}

void Airport_Database::board(string passengerName, string planeModel)
{
    dbms.execute("INSERT INTO Boarding VALUES FROM (\"" + passengerName + "\", "
                                                   "\"" + planeModel    + "\");");
}

void Airport_Database::own(string airlineName, string planeModel)
{
    dbms.execute("INSERT INTO Owns VALUES FROM (\"" + airlineName + "\", "
                                               "\"" + planeModel  + "\");");
}

void Airport_Database::removePassenger(string name, string list)
{
    if(passengerLists.find(list) == passengerLists.end())
            throw "List not found!";

    dbms.execute("DELETE FROM " + list + " WHERE name == \"" + name + "\";");
}

void Airport_Database::removePlane(string model, string list)
{
    if(planeLists.find(list) == planeLists.end())
            throw "List not found!";

    dbms.execute("DELETE FROM " + list + " WHERE model == \"" + model + "\";");
}

void Airport_Database::removeAirline(string name, string list)
{
    if(airlineLists.find(list) == airlineLists.end())
            throw "List not found!";

    dbms.execute("DELETE FROM " + list + " WHERE name == \"" + name + "\";");
}

void Airport_Database::disembark(string passengerName, string planeModel)
{
    dbms.execute("DELETE FROM Boarding WHERE passengerName == \"" + passengerName + '"'
                                       + "&& planeModel    == \"" + planeModel    + "\";");
}

void Airport_Database::disown(string airlineName, string planeModel)
{
    dbms.execute("DELETE FROM Boarding WHERE airlineName == \"" + airlineName + '"'
                                       + "&& planeModel  == \"" + planeModel  + "\";");
}

void Airport_Database::updatePassenger(string name, string list, int updatedBaggage)
{
    dbms.execute("UPDATE " + list + " SET baggage = " + to_string(updatedBaggage)
                                  + " WHERE name == \"" + name + "\";");
}

void Airport_Database::updateAirline(string name, string list, string newHQ)
{
    dbms.execute("UPDATE " + list + " SET baggage = \"" + name  + '"'
                                  + " WHERE name == \"" + newHQ + "\";");
}

void Airport_Database::save(string list)
{
    dbms.execute("WRITE Boarding;");
    dbms.execute("WRITE Owns;");
    for(string list : planeLists)
        dbms.execute("WRITE " + list + ";");
    for(string list : passengerLists)
        dbms.execute("WRITE " + list + ";");
    for(string list : airlineLists)
        dbms.execute("WRITE " + list + ";");

}

void Airport_Database::load(string list)
{
    dbms.execute("OPEN Boarding;");
    dbms.execute("OPEN Owns;");
    for(string list : planeLists)
        dbms.execute("OPEN " + list + ";");
    for(string list : passengerLists)
        dbms.execute("OPEN " + list + ";");
    for(string list : airlineLists)
        dbms.execute("OPEN " + list + ";");
}

void Airport_Database::merge(string list1, string list2)
{

}

void Airport_Database::subtract(string list1, string list2)
{

}

vector<string> Airport_Database::listPassengerNames(string list)
{
    return vector<string>();
}

vector<string> Airport_Database::filterHeavyBaggage(string list, int baggageLimit /*= 23*/)
{
    return vector<string>();
}
