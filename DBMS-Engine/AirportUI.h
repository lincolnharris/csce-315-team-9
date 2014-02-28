/*
 * AirportDBInterface.h
 *
 *  Created on: Feb 25, 2014
 *      Author: Synix
 */

#pragma once

#include <map>
#include <functional>

#include "AirportDB.h"


/* A list of pairs, each pair is a menu option, consisting of the
 * option's text and its corresponding action.
 * The action is a function that does not take any arguments and
 * does not return anything.
 * Because the functions are memeber functions, they implicitly
 * take in 'this' (AirportUI&) as an argument.
 * Just look at the type name, it's beautiful! :D
 */
typedef std::vector<std::pair<std::string, std::function<void()>>> Menu;


class AirportUI
{
    AirportDB database;
    Menu *start_menu, *create_list_menu, *new_entry_menu,
         *remove_entry_menu, *update_entry_menu;

    // IO
    void open_list();
    void save_list();
    void show_list();

    // Creation
    void add_passenger_list();
    void add_airline_list();
    void add_plane_list();

    // Adding
    void add_passenger();
    void add_airline();
    void add_plane();
    void add_owning();
    void add_boarding();

    // Removing
    void remove_passenger();
    void remove_airline();
    void remove_plane();
    void remove_owning();
    void remove_boarding();

    // Updating
    void update_passenger();
    void update_airline();

    // Relational
    void merge_lists();
    void subtract_lists();

    void list_passenger_names();
    void filter_heavy_baggage();
	void natural_join();


    static void present_menu(Menu* menu);

public:
    AirportUI();
};

