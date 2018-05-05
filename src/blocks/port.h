#ifndef PORT_H
#define PORT_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>
#include <algorithm>

#include <QString>

class Block;

using namespace std;
class Port
{
	public:
		Port();
		Port(string name, bool declaredType);
		Port(vector<string> arrayOfNames, bool declaredType);
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
        //static const bool inputType = true;
        //static const bool outputType = false;
        QString print();
        QString printConnection();
        bool isInputType();
        bool isOutputType();

	protected:
		map<string, double> content;
	private:
		bool type;
		Port* connectedPort = NULL;
		Block* ownerBlock = NULL;
};


#endif // PORT_H
