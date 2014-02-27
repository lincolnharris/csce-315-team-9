/*
 * AirportDBInterface.cpp
 *
 *  Created on: Feb 25, 2014
 *      Author: Synix
 */

#include "AirportUI.h"

#include <iostream>
#include <sstream>

using namespace std;


AirportUI::AirportUI()
{
    /* start_menu needs to pass create_list_menu to bind when it's being initialized,
     * but create_list_menu is not initialized yet, so an empty menu is being
     * passed to the bind function call.
     * The same is true for create_list_menu, so it's a cyclic dependency.
     * To avoid this, I passed the POINTER to the actual Menu object, so I
     * can preallocate the Menu objects before I pass them to bind.
     */
    start_menu        = new Menu;
    create_list_menu  = new Menu;
    new_entry_menu    = new Menu;
    remove_entry_menu = new Menu;
    update_entry_menu = new Menu;

    *start_menu = {
            { "Create a new list",            bind(present_menu, create_list_menu) },
            { "Open a previously saved list", bind(&AirportUI::open_list, this) },
            { "Save a list",                  bind(&AirportUI::save_list, this) },
            { "Add an entry to a list",       bind(present_menu, new_entry_menu) },
            { "Remove an entry from a list",  bind(present_menu, remove_entry_menu) },
            { "Update an entry in a list",    bind(present_menu, update_entry_menu) },
            { "Merge two lists",              bind(&AirportUI::merge_lists, this) },
            { "Subtract two lists",           bind(&AirportUI::subtract_lists, this) },
            { "List passenger names",         bind(&AirportUI::list_passenger_names, this) },
            { "Filter out passengers with "
              "heavy baggage",                bind(&AirportUI::filter_heavy_baggage, this) },
            { "Exit",                         []() { exit(0); } },
    };

    *create_list_menu = {
            { "List of passengers", bind(&AirportUI::add_passenger_list, this) },
            { "List of airlines",   bind(&AirportUI::add_airline_list, this) },
            { "List of planes",     bind(&AirportUI::add_plane_list, this) },
            { "Back",               bind(present_menu, start_menu) },
    };

    *new_entry_menu = {
            { "Add a passenger",           bind(&AirportUI::add_passenger, this) },
            { "Add an airline",            bind(&AirportUI::add_airline, this) },
            { "Add a plane",               bind(&AirportUI::add_plane, this) },
            { "Add an ownership relation", bind(&AirportUI::add_owning, this) },
            { "Add a boarding relation",   bind(&AirportUI::add_boarding, this) },
            { "Back",                      bind(present_menu, start_menu) },
    };

    *remove_entry_menu = {
            { "Remove a passenger",           bind(&AirportUI::remove_passenger, this) },
            { "Remove an airline",            bind(&AirportUI::remove_airline, this) },
            { "Remove a plane",               bind(&AirportUI::remove_plane, this) },
            { "Remove an ownership relation", bind(&AirportUI::remove_owning, this) },
            { "Remove a boarding relation",   bind(&AirportUI::remove_boarding, this) },
            { "Back",                         bind(present_menu, start_menu) },
    };

    *update_entry_menu = {
            { "Change a passenger's baggage", bind(&AirportUI::update_passenger, this) },
            { "Change an airline's HQ",       bind(&AirportUI::update_airline, this) },
            { "Back",                         bind(present_menu, start_menu) },
    };

    while(true) present_menu(start_menu);
}

void AirportUI::present_menu(Menu* menu)
{
    // Writing the menu on the screen:
    cout << "---------------------------------------------" << endl;
    int i = 1;
    for(auto& option : *menu) // <option text, action>
        cout << '(' << i++ << ") " << option.first << endl;
    cout << endl << "Please type the index of your desired option:" << endl;

    // Getting user input:
    /* Nearly impossible and a PITA to gracefully handle invalid user input
     * and recover from exceptions. cin.ignore + clear + sync and reading
     * with getline seem to handle all the BS that I/O threw at me.
     */
    int choice;
    while(true)
    {
        stringstream ss;
        string userInput;
        getline(cin, userInput);
        ss << userInput;
        if(!(ss >> choice))
        {
            cout << "Please type a valid integer." << endl;
            continue;
        }
        break;
    }

    // Executing the respective option:
    try { menu->at(choice - 1).second(); }
    catch(const char* c)
    {
        // The combination of all 3 of these seemed to flush cin for me.
        // The problem is that sync is implementation defined.
        cin.clear(); cin.sync();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Possible invalid input! Error: <" << c << '>' << endl;
        present_menu(menu);
    }
    catch (...)
    {
        cin.clear(); cin.sync();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "An error has occurred. Possible engine failure!";
    }
}

void AirportUI::add_passenger_list()
{
    cout << "Enter the list's name:" << endl;
    string name;
    if(!(cin >> name))
        cout << "Invalid input! Please try again." << endl;
    database.newPassengerList(name);
}

void AirportUI::add_airline_list()
{
    //TODO
}

void AirportUI::add_plane_list()
{
    //TODO
}

void AirportUI::add_passenger()
{
    cout << "Enter the passenger's name, age, baggage, destination, and the name of the "
            "list to which you want to add the passenger, separated by space:" << endl;
    int age, baggage;
    string name, destination, list;
    if(!(cin >> name >> age >> baggage >> destination >> list))
        throw "Invalid input! Try again!";
    database.addPassenger(name, age, baggage, destination, list);
}

void AirportUI::add_plane()
{
    cout << "Enter the plane's model, capacity, and the name of the "
            "list to which you want to add the plane, separated by space:" << endl;
    int capacity;
    string model, list;
    while(!(cin >> model >> capacity >> list))
        throw "Invalid input! Try again!";
    database.addPlane(model, capacity, list);
}

void AirportUI::add_airline()
{
    //TODO
}

void AirportUI::open_list()
{
    cout << "Enter the name of the list to open:" << endl;
    string listName;
    if(!(cin >> listName))
        throw "Invalid input! Try again!";
    database.load(listName);
}

void AirportUI::save_list()
{
    cout << "Enter the name of the list to save:" << endl;
    string listName;
    if(!(cin >> listName))
        throw "Invalid input! Try again!";
    database.save(listName);
}

void AirportUI::save_list()
{
    cout << "Enter the name of the list to show:" << endl;
    string listName;
    if(!(cin >> listName))
        throw "Invalid input! Try again!";
    database.show(listName);
}

void AirportUI::add_owning()
{

    //TODO
}

void AirportUI::add_boarding()
{
    //TODO
}

void AirportUI::remove_passenger()
{
    cout << "Enter the name of the passenger and the list from which "
            "you want to remove the passenger, separated by space:" << endl;
    string name,list;
    if(!(cin >> name >> list))
        throw "Invalid input! Try again!";
    database.removePassenger(name, list);
}

void AirportUI::remove_airline()
{
    //todo
}

void AirportUI::remove_plane()
{
    //todo
}

void AirportUI::remove_owning()
{
    //todo
}

void AirportUI::remove_boarding()
{
    //todo
}

void AirportUI::update_passenger()
{
    cout << "Enter the name of the passenger, the updated baggage value, and the "
            "list from which you want to remove the passenger, separated by space:" << endl;
    int baggage;
    string name, list;
    if(!(cin >> name >> baggage >> list))
        throw "Invalid input! Try again!";
    database.updatePassenger(name, list, baggage);
}

void AirportUI::update_airline()
{

    //todo
}

void AirportUI::merge_lists()
{
    cout << "Enter the name of two lists to merge, separated by space:" << endl;
    string list1, list2;
    if(!(cin >> list1 >> list2))
        throw "Invalid input! Try again!";
    database.merge(list1, list2);
}

void AirportUI::subtract_lists()
{
    cout << "Enter the name of two lists to subtract, separated by space:"
            "(order matters)" << endl;
    string list1, list2;
    if(!(cin >> list1 >> list2))
        throw "Invalid input! Try again!";
    database.subtract(list1, list2);
}

void AirportUI::list_passenger_names()
{
    cout << "Enter the list's name:" << endl;
    string name;
    if(!(cin >> name))
        cout << "Invalid input! Please try again." << endl;
    database.listPassengerNames(name);
}

void AirportUI::filter_heavy_baggage()
{
    cout << "Enter the list's name, followed by the baggage limit, "
            "separated by space:" << endl;
    string name;
    int limit;
    if(!(cin >> name >> limit))
        cout << "Invalid input! Please try again." << endl;
    database.filterHeavyBaggage(name, limit);
}


int main()
{
    AirportUI();
    return 0;
}
