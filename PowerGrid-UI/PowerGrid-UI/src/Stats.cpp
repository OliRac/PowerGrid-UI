#include "Stats.h"
#include "Connection.h"


Stats::Stats(){
	/*Adding some data, quick and dirty.*/
	numPlayers = 2;

	/*Starting regions*/
	startRegions.push_back("Rohan");
	startRegions.push_back("Shire");

	/*Player locations*/
	vector<string> l1;
	l1.push_back("Edoras");
	l1.push_back("Rivendell");

	vector<string> l2;
	l2.push_back("Bree");

	locations.push_back(l1);
	locations.push_back(l2);

	/*Cash*/
	cash.push_back(85);
	cash.push_back(27);

	/*Cities*/
	vector<int> c1;
	c1.push_back(3);
	c1.push_back(8);

	vector<int> c2;
	c2.push_back(2);

	castles.push_back(c1);
	castles.push_back(c2);

	/*Resource counts*/
	vector<int> r1(4);
	r1[0] = 20;
	r1[1] = 18;
	r1[2] = 12;
	r1[3] = 1;

	vector<int> r2(4);
	r2[0] = 3;
	r2[1] = 7;
	r2[2] = 5;
	r2[3] = 0;

	resources.push_back(r1);
	resources.push_back(r2);

	/*Connections*/
	Connection conn1("A", "B", 5);
	Connection conn2("C", "D", 13);
	Connection conn3("A", "D", 7);
	Connection conn4("B", "E", 2);

	connections.push_back(conn1);
	connections.push_back(conn2);
	connections.push_back(conn3);
	connections.push_back(conn4);

	/*Shop contents*/
	shop.push_back(20);
	shop.push_back(13);
	shop.push_back(5);
	shop.push_back(2);
}


Stats::~Stats(){

}

int Stats::getNumPlayers(){
	return numPlayers;
}

vector<string> Stats::getStartRegions(){
	return startRegions;
}

vector<vector<string>> Stats::getLocations(){
	return locations;
}

vector<int> Stats::getCash(){
	return cash;
}

vector<vector<int>> Stats::getCastles(){
	return castles;
}

vector<vector<int>> Stats::getResources(){
	return resources;
}

vector<Connection > Stats::getConnections(){
	return connections;
}

vector<int> Stats::getShop(){
	return shop;
}
