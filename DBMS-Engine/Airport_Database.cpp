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
}


Airport_Database::~Airport_Database()
{
}

void Airport_Database::newAirlineList(const string& name)
{

}

void Airport_Database::newPassengerList(const string& name)
{

}

void Airport_Database::newPlaneList(const string& name)
{

}

void Airport_Database::addPlane(const string& model, int capacity, const string& list)
{

}

void Airport_Database::addPassenger(const string& name, int age, int baggage, const string& destination, const string& list)
{

}

void Airport_Database::addAirline(const string& name, const string& HQ, const string& list)
{

}

void Airport_Database::board(const string& passengerName, const string& planeModel)
{

}

void Airport_Database::own(const string& airlineName, const string& planeModel)
{

}

void Airport_Database::removePassenger(const string& name, const string& list)
{

}

void Airport_Database::removePlane(const string& model, const string& list)
{

}

void Airport_Database::removeAirline(const string& name, const string& list)
{

}

void Airport_Database::disembark(const string& passengerName, const string& planeModel)
{

}

void Airport_Database::disown(const string& airlineName, const string& planeModel)
{

}

void Airport_Database::updatePassenger(const string& name, const string& list, int updatedBaggage)
{

}

void Airport_Database::updateAirline(const string& name, const string& list, const string& newHQ)
{

}

void Airport_Database::save(const string& list)
{
    dbms.write_cmd(list);
}

void Airport_Database::load(const string& list)
{
    dbms.open_cmd(list);
}

void Airport_Database::merge(const string& list1, const string& list2)
{

}

void Airport_Database::subtract(const string& list1, const string& list2)
{

}

vector<string> Airport_Database::listPassengerNames(const string& list)
{
    return vector<string>();
}

vector<string> Airport_Database::filterHeavyBaggage(const string& list, int baggageLimit /*= 23*/)
{
    return vector<string>();
}
