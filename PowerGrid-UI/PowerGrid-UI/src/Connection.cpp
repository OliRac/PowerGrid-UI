#include "Connection.h"

Connection::Connection()
{
}


Connection::~Connection()
{
}

string Connection::getSource(){
	return source;
}

string Connection::getTarget(){
	return target;
}

int Connection::getCost(){
	return cost;
}
