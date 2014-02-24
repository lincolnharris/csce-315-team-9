/*
* Airport_Database.h
*
*  Created on: Feb 23, 2014
*      Author: Synix
*/
#pragma once
#include <string>
#include <vector>

#include "DBMS.h"

using std::string;
using std::vector;

class Airport_Database
{
    DBMS dbms;

public:
    Airport_Database();
    ~Airport_Database();

    // Creation
    void newAirlineList(const string& name);
    void newPassengerList(const string& name);
    void newPlaneList(const string& name);

    // Adding
    void addAirline(const string& name, const string& HQ, const string& list);
    void addPassenger(const string& name, int age, int baggage, 
                      const string& destination, const string& list);
    void addPlane(const string& model, int capacity, const string& list);

    void board(const string& passengerName, const string& planeModel);
    void own(const string& airlineName, const string& planeModel);

    // Removing
    void removePassenger(const string& name, const string& list);
    void removePlane(const string& model, const string& list);
    void removeAirline(const string& name, const string& list);

    void disembark(const string& passengerName, const string& planeModel);
    void disown(const string& airlineName, const string& planeModel);

    // Updating
    void updatePassenger(const string& name, const string& list, int updatedBaggage);
    void updateAirline(const string& name, const string& list, const string& newHQ);

    // File IO
    void save(const string& list);
    void load(const string& list);

    // Relational
    void merge(const string& list1, const string& list2);    // Union
    void subtract(const string& list1, const string& list2); // Subtraction

    vector<string> listPassengerNames(const string& list);   // Projection
                                                             // Selection
    vector<string> filterHeavyBaggage(const string& list, int baggageLimit = 23); 

};

