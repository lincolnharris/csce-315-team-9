#include "Parser.h"

bool Parser::open_cmd(){
	int start = counter;

	if( tokens[counter].str != "OPEN" ){
		counter = start;
		return false;
	}
	++counter;

	auto name = relation_name();
	if( !name )
    {
        counter = start; // Backtrack
        return false;
    }
    dbms->open_cmd(name);
    return true;
}

bool Parser::close_cmd(){
	int start = counter;

	if( tokens[counter].str != "CLOSE" ){
		counter = start;
		return false;
	}
	++counter;

	auto name = relation_name();
	if( !name )
    {
        counter = start; // Backtrack
        return false;
    }
    dbms->close_cmd(name);
    return true;
}

bool Parser::write_cmd(){
	int start = counter;

	if( tokens[counter].str != "WRITE" ){
		counter = start;
		return false;
	}
	++counter;

	auto name = relation_name();
	if( !name )
    {
        counter = start; // Backtrack
        return false;
    }
    dbms->write_cmd(name);
    return true;
}

bool Parser::exit_cmd(){
	int start = counter;

	if( tokens[counter].str != "EXIT" ){
		counter = start;
		return false;
	}
	++counter;
	dbms->exit_cmd();
	return true;
}

bool Parser::show_cmd(){
	int start = counter;

	if( tokens[counter].str != "SHOW" ){
		counter = start;
		return false;
	}
	++counter;

	auto table = atomic_expr();
	if( !table )
    {
        counter = start; // Backtrack
        return false;
    }

    dbms->show_cmd(table);
    return true;
}

bool Parser::create_cmd(){
	int start = counter;

	if( tokens[counter].str != "CREATE" ){
		counter = start;
		return false;
	}
	++counter;
	if( tokens[counter].str != "TABLE" ){
		counter = start;
		return false;
	}
    ++counter;

    auto name = relation_name();
    if( !name )
    {
        counter = start; // Backtrack
        return false;
    }

	if(tokens[counter].str != "("){
		counter = start;
		return false;
	}
	++counter;

    auto typed_att_list = type_attribute_list();
    if( !typed_att_list ){
        counter = start;
        return false;
    }

    if( tokens[counter].str != ")" ){
        counter = start;
        return false;
    }
    ++counter;

    if( tokens[counter].str != "PRIMARY" ){
        counter = start;
        return false;
    }
    ++counter;

    if( tokens[counter].str != "KEY" ){
        counter = start;
        return false;
    }
    ++counter;

    if( tokens[counter].str != "(" ){
        counter = start;
        return false;
    }
    ++counter;

    auto att_list = attribute_list();
    if( !att_list ){
        counter = start;
        return false;
    }
    ++counter;

    if( tokens[counter].str != ")" ){
        counter = start;
        return false;
    }
    ++counter;

    dbms->create_cmd(name, typed_att_list, att_list);
    return true;
}

bool Parser::update_cmd(){
    int start = counter;

    if( tokens[counter].str != "UPDATE" ){
        counter = start;
        return false;
    }
    ++counter;

    auto Rname = relation_name();
    if( !Rname ){
        counter = start;
        return false;
    }

    if( tokens[counter].str != "SET" ){
        counter = start;
        return false;
    }
    ++counter;

    auto Aname = attribute_name();
    if( !Aname ){
        counter = start;
        return false;
    }

    if( tokens[counter].str != "=" ){
        counter = start;
        return false;
    }
    ++counter;

    auto lit = literal();
    if( !lit ){
        counter = start;
        return false;
    }

    vector<string> Anames;
    Anames.push_back(Aname);
    vector<string> lits;
    lits.push_back(lit);

    while(true){
        int tempStart = counter;

        if( tokens[counter].str != "," ){
            counter = tempStart;
            break;
        }

        Aname = attribute_name();
        if( !Aname ) {
            counter = tempStart;
            break;
        }
        if( tokens[counter].str != "=" ){
            counter = tempStart;
            break;
        }
        ++counter;
        lit = literal();
        if( !lit ) {
            counter = tempStart;
            break;
        }
        Anames.push_back(Aname);
        lits.push_back(lit);
    }

    if( tokens[counter].str != "WHERE" ){
        counter = start;
        return false;
    }
    ++counter;

    auto cond = condition();
    if( !cond ) {
        counter = start;
        return false;
    }


    unordered_map<string,Table>::iterator it = dbms->relations.find(Rname);
    //dbms->update_cmd(it->second, ) needs to be looked at
    return true;
}

bool Parser::insert_cmd(){
    int start = counter;

    if( tokens[counter].str != "INSERT" ){
        counter = start;
        return false;
    }
    ++counter;

    if( tokens[counter].str != "INTO" ){
        counter = start;
        return false;
    }
    ++counter;

    auto name = relation_name();
    if( !name ) {
        counter = start;
        return false;
    }

    if( tokens[counter].str != "VALUES" ){
        counter = start;
        return false;
    }
    ++counter;
    if( tokens[counter].str != "FROM" ){
        counter = start;
        return false;
    }
    ++counter;

    
    if(tokens[counter].str == "RELATION" ) {
        ++counter;
        auto exp = expr();
        if( !exp ){
            counter = start;
            return false;
        }
        unordered_map<string,Table>::iterator it = dbms->relations.find(name);
        dbms->insert_cmd(it->second, exp );
        return true;
    }
    else {
        if(tokens[counter].str == "(" ) {
            ++counter;
            auto lit = literal();
            if( !lit ){
                counter = start;
                return false;
            }
            vector<string> lits;
            lits.push_back(lit);
            while(true){
                int tempStart = counter;

                if(tokens[counter].str != "," ) {
                    counter = tempStart;
                    break;
                }
                ++counter;
                lit = literal();
                if( !lit ) {
                    counter = tempStart;
                    break;
                }
            }

            if( tokens[counter] != ")" ){
                counter = start;
                return false;
            }
            unordered_map<string,Table>::iterator it = dbms->relations.find(name);
            //dbms-> insert( it->second, something else);
            return true;

        }
        else{
            counter = start;
            return false;
        }
    }
}

bool Parser::delete_cmd(){
    int start = counter;

    if( tokens[counter].str != "DELETE" ){
        counter = start;
        return false;
    }
    ++counter;
    if( tokens[counter].str != "FROM" ){
        counter = start;
        return false;
    }
    ++counter;

    auto name = relation_name();
    if( !name ){
        counter = start;
        return false;
    }

    if( tokens[counter].str != "WHERE" ){
        counter = start;
        return false;
    }
    ++counter;

    auto cond = condition();
    if( !cond ){
        counter = start;
        return false;
    }

    unordered_map<string,Table>::iterator it = dbms->relations.find(name);
    dbms->delete_cmd(it->second, cond);
    return true;
}

ParsedResult<vector<string>> Parser::typed_attribute_list(){
	int start = counter;
	
	auto name = attribute_name();
	if ( !name ){
		counter = start;
		return false;
	}
	++counter;
	
	auto t = type();
	if( !t ){
		counter = start;
		return false;
	}
	++counter;
	
	vector<string> names;
	vecotr<Type> ts;
	names.push_back(name);
	ts.push_back(t);
	while(true){
		int tempStart = counter;
		if( tokens[counter] != "," ){
			counter = tempStart;
			break;
		}
		++counter;
		name = attribute_name();
		if( !name) {
			counter = tempStart;
			break;
		}
		t  = type();
		if( !t ) {
			counter = tempStart;
			break;
		}
		names.push_back(name);
		ts.push_back(t);
	}
	
	int size = names.size();
	vector<pair<string, Type> > result;
	for(int i=0; i<size; ++i){
		pair<string,Type> temp(names[i], ts[i]);
		result.push_back(temp);
	}
	return result;
}

ParsedResult<Type> Parser::type(){
	int start = counter;
	
	if( tokens[counter] == "VARCHAR" ){
		++counter;
		if( tokens[counter] != "(" ) {
			counter = start;
			return false;
		}
		++counter;
		int integr = integer();
		if( !integr ){
			counter = start;
			return false;
		}
		if( tokens[counter] != ")" ) {
			counter = start;
			return false;
		}
		return Type(1,integr);
	}
	else if ( tokens[counter] == "INTEGER") {
		return Type(1,-1);
	}
	else{
		counter = start;
		return false;
	}
}


ParsedResult<int> Parser::integer(){
	int start = counter;
	
	int integr = atoi(tokens[counter]);
	int size = tokens[counter].length();
	if( integr == 0){
		counter = start;
		return false;
	}
	return integr;
}

ParsedResult<Table> PARSER::program(){
	int start = counter;
	
	auto qry = query();
	if( !qry ){
		//auto cmmd = command();
		//if ( !cmmd ){
		//	counter = start;
		//	return false;
		//}
		//else{
		//
		//}
		return Table(); //just for now until command() is made
	}
	else return qry;
}
