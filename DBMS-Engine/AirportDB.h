/*
* Airport_Database.h
*
*  Created on: Feb 23, 2014
*      Author: Synix
*/
#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <list>

#include "DBMS.h"

using std::string;
using std::vector;
using std::unordered_set;
using std::list;

class AirportDB
{
    DBMS dbms;

    unordered_set<string> lists;

public:
    AirportDB();
    ~AirportDB();

    // Creation
    void newAirlineList(string name);
    void newPassengerList(string name);
    void newPlaneList(string name);

    // Adding
    void addAirline(string name, string HQ, string list);
    void addPassenger(string name, int age, int baggage,
                      string destination, string list);
    void addPlane(string model, int capacity, string list);

    void board(string passengerName, string planeModel);
    void own(string airlineName, string planeModel);

    // Removing
    void removePassenger(string name, string list);
    void removePlane(string model, string list);
    void removeAirline(string name, string list);

    void disembark(string passengerName, string planeModel);
    void disown(string airlineName, string planeModel);

    // Updating
    void updatePassenger(string name, string list, int updatedBaggage);
    void updateAirline(string name, string list, string newHQ);

    // IO
    void save(string list);
    void load(string list);
    void show(string list);

    // Relational
    void merge(string list1, string list2);    // Union
    void subtract(string list1, string list2); // Subtraction

    vector<string> listPassengerNames(string list);   // Projection
                                                      // Selection
    list<vector<string>> filterHeavyBaggage(string list, int baggageLimit);

	void natural_join(string list1, string list2);

};

