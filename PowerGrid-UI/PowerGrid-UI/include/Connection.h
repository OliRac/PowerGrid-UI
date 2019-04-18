#pragma once
#include <string>

using std::string;

class Connection
{
public:
	Connection();
	Connection(string src, string tgt, int n) : source(src), target(tgt), cost(n) {}
	~Connection();

	string getSource();
	string getTarget();
	int getCost();

private:
	string source;
	string target;
	int cost;
};

