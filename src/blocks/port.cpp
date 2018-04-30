/*#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>*/

#include "port.h"



Port::Port () 
{
}

Port::Port (string name) 
{
	content.insert(std::make_pair(name, numeric_limits<double>::quiet_NaN()));
}

Port::Port (vector<string> arrayOfNames) 
{
	for (string name : arrayOfNames)
		content.insert(std::make_pair(name, numeric_limits<double>::quiet_NaN()));
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
		connectedPort = other;
		other->connectedPort = this;
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

int main(void)
{
	
	

}
