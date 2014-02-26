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
    start_menu       = new Menu;
    create_list_menu = new Menu;
    new_entry_menu   = new Menu;

    *start_menu = {
            { "Create a new list", bind(present_menu, create_list_menu) },
            { "Open a previously saved list", bind(&AirportUI::open_list, this) },
            { "Save a list", bind(&AirportUI::save_list, this) },
            { "Add an entry to a list", bind(present_menu, new_entry_menu) },
            { "Exit", []() { exit(0); } },
    };

    *create_list_menu = {
            { "List of passengers", bind(&AirportUI::add_passenger_list, this) },
            { "List of airlines", bind(&AirportUI::add_airline_list, this) },
            { "List of planes", bind(&AirportUI::add_plane_list, this) },
            { "Back", bind(present_menu, start_menu) },
    };

    *new_entry_menu = {
            { "List of passengers", bind(&AirportUI::add_passenger, this) },
            { "List of airlines", bind(&AirportUI::add_airline, this) },
            { "List of planes", bind(&AirportUI::add_plane, this) },
            { "Back", bind(present_menu, start_menu) },
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
    {
        cout << "Invalid input! Please try again." << endl;
        present_menu(create_list_menu);
    }
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


int main()
{
    AirportUI();
    return 0;
}
