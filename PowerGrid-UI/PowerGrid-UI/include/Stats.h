#pragma once
#include <vector>
#include <string>

#include "Connection.h"

using std::vector;
using std::string;

class Stats{
public:
	Stats();
	~Stats();

	int getNumPlayers();
	vector<string> getStartRegions();
	vector< vector<string> > getLocations();
	vector<int> getCash();
	vector< vector<int> > getCastles();
	vector< vector<int> > getResources();
	vector< Connection > getConnections();
	vector<int> getShop();

private:
	int numPlayers;
	vector<string> startRegions;
	vector< vector<string> > locations;
	vector<int> cash;
	vector< vector<int> > castles;
	vector< vector<int> > resources;
	vector< Connection > connections;
	vector<int> shop;
};

