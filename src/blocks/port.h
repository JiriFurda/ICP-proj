#ifndef PORT_H
#define PORT_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>
#include <algorithm>

class Block;

using namespace std;
class Port
{
	public:
		Port();
		Port(string name);
		Port(vector<string> arrayOfNames);
		bool compatible(Port other);
		bool setValue(string name, double value);
		double getValue(string name);
		map<string, double> getContent();
		vector<string> getNames();
	//	string getName(); not needed?
		bool setConnectedPort(Port* other);
		Port* getConnectedPort();
		Block* getOwnerBlock();
		void setOwnerBlock(Block* otherBlock);
		

	protected:
		map<string, double> content;
	private:
		Port* connectedPort = NULL;
		Block* ownerBlock = NULL;
};


#endif // PORT_H
