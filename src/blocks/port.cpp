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

Port::Port (string name, bool declaredType) 
{

	type = declaredType;
	////cout << "Port::Port (string name)1\n";
	
	content.insert(std::make_pair(name, numeric_limits<double>::quiet_NaN()));
	////cout << "Port::Port (string name)2\n";
}

Port::Port (vector<string> arrayOfNames, bool declaredType) 
{
	type = declaredType;
	////cout << "Port::Port (vector<string> arrayOfNames) \n";
	for (string name : arrayOfNames)
		content.insert(std::make_pair(name, numeric_limits<double>::quiet_NaN()));
	////cout << "Port::Port (vector<string> arrayOfNames) \n";
}

bool Port::compatible(Port other)
{
	return getNames() == other.getNames();
	
}

bool Port::setValue(string name, double value)
{
	//cout << "Port::setValue\n";
	map<string, double>::iterator it = content.find(name); 
	if (it != content.end())
	{
		it->second = value;
	}
		
	else
		return false;

	if (type && connectedPort != NULL)
		return connectedPort->setValue(name, value);

	return true;	
}

double Port::getValue(string name)
{
	//cout << "Port::getValue\n";
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

		
Block* Port::getOwnerBlock()
{
	////cout << "Port::getOwnerBlock" << ownerBlock << "\n";
	return ownerBlock;
}

void Port::setOwnerBlock(Block* otherBlock)
{
	////cout << "______Port::setOwnerBlock___   " << otherBlock << "\n";

	ownerBlock = otherBlock;
}

QString Port::print()
{
    vector<string> names = this->getNames();
    QString result;

    for(vector<string>::iterator name = names.begin(); name != names.end(); ++name)
    {
        result.append("["+QString::fromStdString(*name)+"]");
    }

    if(this->getConnectedPort() == NULL)
        result.append(" Not connected");
    else
        result.append(" Connected");

    return result;  // [real][imaginary] Not connected
}

QString Port::printConnection()
{
    vector<string> names = this->getNames();
    QString result;
    bool first = true; // Don't insert comma at beginning

    for(vector<string>::iterator name = names.begin(); name != names.end(); ++name)
    {
        if(!first)
            result.append(", ");
        else
            first = false;

        result.append("["+QString::fromStdString(*name)+"] ");
        result.append(QString::number(this->getValue(*name)));
    }

    return result;  // [real] 42, [imaginary] 78
    return NULL;
}

bool Port::isInputType()
{
    return !this->isOutputType();
}

bool Port::isOutputType()
{
    return this->type;
}
