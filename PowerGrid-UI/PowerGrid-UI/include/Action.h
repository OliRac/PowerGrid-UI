#pragma once
#include <string>

using std::string;

class Action{
public:
	Action();
	~Action();

	string getPhaseMsg();
	string getActionMsg();
	int getPlayerID();

private:
	string phaseMsg;
	string actionMsg;
	int playerID;
};

