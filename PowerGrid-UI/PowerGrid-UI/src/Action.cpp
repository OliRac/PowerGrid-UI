#include "Action.h"



Action::Action(){
	phaseMsg = "Viewing phase";
	actionMsg = "Checking out a basic UI!";
	playerID = 1;
}


Action::~Action(){

}

string Action::getPhaseMsg(){
	return phaseMsg;
}

string Action::getActionMsg(){
	return actionMsg;
}

int Action::getPlayerID(){
	return playerID;
}
