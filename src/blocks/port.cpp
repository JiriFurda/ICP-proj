/*#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>*/

#include "port.h"
#include "block.h"



Port::Port () 
{
}

Port::Port (string name) 
{
	//cout << "Port::Port (string name)1\n";
	content.insert(std::make_pair(name, numeric_limits<double>::quiet_NaN()));
	//cout << "Port::Port (string name)2\n";
}

Port::Port (vector<string> arrayOfNames) 
{
	//cout << "Port::Port (vector<string> arrayOfNames) \n";
	for (string name : arrayOfNames)
		content.insert(std::make_pair(name, numeric_limits<double>::quiet_NaN()));
	//cout << "Port::Port (vector<string> arrayOfNames) \n";
}

bool Port::compatible(Port other)
{
	return getNames() == other.getNames();
	
}

bool Port::setValue(string name, double value)
{
	map<string, double>::iterator it = content.find(name); 
	if (it != content.end())
	{
		it->second = value;
		return true;
	}
		
	else
		return false;
}

double Port::getValue(string name)
{
	map<string, double>::iterator it = content.find(name);
	if (it != content.end())
		return it->second;
	else
	{
		cerr << "attempt to find non-existing key\n";
		exit(-1);
	}
}

map<string, double> Port::getContent()
{
	return content;
}



vector<string> Port::getNames()
{
	vector<string> names;
	for(map<string,double>::iterator it = content.begin(); it != content.end(); ++it)
		names.push_back(it->first);
	return names;
}

bool Port::setConnectedPort(Port* other)
{
	if (compatible(*other))
	{
	//	cout << "Port::setConnectedPort before: " << connectedPort->getOwnerBlock() << "\n";
		connectedPort = other;
	//	cout << "Port::setConnectedPort after: " << connectedPort->getOwnerBlock() << "\n";
		other->connectedPort = this;
		//cout << "Port::setConnectedPort after: " << other->connectedPort->getOwnerBlock() << "\n";
		return true;
	}

	else
	{
		cerr << "Port::setConnectedPort: Port types are incompatible\n";
		return false;
	}
}

Port* Port::getConnectedPort()
{
	return connectedPort;
}

		
Block* Port::getOwnerBlock()
{
	//cout << "Port::getOwnerBlock" << ownerBlock << "\n";
	return ownerBlock;
}

void Port::setOwnerBlock(Block* otherBlock)
{
	//cout << "______Port::setOwnerBlock___   " << otherBlock << "\n";
	ownerBlock = otherBlock;
}
