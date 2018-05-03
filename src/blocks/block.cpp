#include "block.h"
#include "port.h"

using namespace std;

Block::Block(vector<Port> in, vector<Port> out)
{
	inputPorts = in;
	outputPorts = out;
	setPorts();
}

Block::Block(Port in, Port out)
{
	inputPorts.push_back(in);
	outputPorts.push_back(out);
	setPorts();
}

Block::Block(vector<Port> in, Port out)
{
	//cout << "this: " << this << "\n";
	//cout << "Block::Block\n";
	inputPorts = in;
	outputPorts.push_back(out);
	//cout << "Block::Block\n";
	setPorts();
}

Block::Block(Port in, vector<Port> out)
{
	inputPorts.push_back(in);
	outputPorts = out;
	setPorts();
}

void Block::execute()
{
	if (executed)
	{
		cerr << "Block::execute(): Found loop\n";
		exit(-1);
	}

/*	for (Port port : getInputPorts())
	{
		vector<double> values;
		for(map<string,double>::iterator it = port.getContent().begin(); it != port.getContent().end(); ++it) 
		{
			values.push_back(it->second);
			cout << it->second << "\n";
		}
		for (double value : values)
		{
			if (value != value) //is value NaN ... value != value is true if value is NaN
			{
				return false;
			}

		}

	}*/

	executeSpecific();
	executed = true;
	//return true;
}

/*void Block::executeSpecific()
{
	cerr << "Block::executeSpecific(): non-overriden member function called\n";
	exit(-1);
}*/

Port* Block::getInputPort(int index)
{
	return &(inputPorts[index]);
}

Port* Block::getOutputPort(int index)
{
	return &(outputPorts[index]);
}

vector<Port> Block::getInputPorts()
{
	return inputPorts;
}

vector<Port> Block::getOutputPorts()
{
	return outputPorts;
}

bool Block::wasExecuted()
{
	return executed;
}

int Block::getID()
{
	//cout << "Block::getID\n";
	//cout << blockID << "\n";
	//cout << "Block::getID\n";	
	return blockID;
}

void Block::setID(int ID)
{
	blockID = ID;
	//cout << "Block::setID\n";
	//cout << blockID << "\n";
}

void Block::setPorts()
{
	//for (Port port : inputPorts)
	for (vector<Port>::iterator it = inputPorts.begin(); it != inputPorts.end(); ++it) 
//    if (*it < 0) *it = -*it;
	{
	//	cout << "**********" << this << "*********\n";
		(*it).setOwnerBlock(this);
	//	cout << "__________" << (*it).getOwnerBlock() << "________\n";
	}

	//for (Port port : outputPorts)
	for (vector<Port>::iterator it = outputPorts.begin(); it != outputPorts.end(); ++it) 
	{
		(*it).setOwnerBlock(this);
	}
}

/*Block::~Block()
{
}
*/
