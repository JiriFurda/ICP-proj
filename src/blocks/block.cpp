#include "block.h"
#include "port.h"

using namespace std;

Block::Block(const vector<Port>& in, const vector<Port>& out)
{
	inputPorts = in;
	outputPorts = out;
	setPorts();
}

Block::Block(const Port& in, const Port& out)
{
	inputPorts.push_back(in);
	outputPorts.push_back(out);
	setPorts();
}

Block::Block(const vector<Port>& in, const Port& out)
{
	inputPorts = in;
	outputPorts.push_back(out);
	setPorts();
}

Block::Block(const Port& in, const vector<Port>& out)
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
			//cout << it->second << "\n";
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
	//cout << "Block::getInputPort\n";
	return &(inputPorts[index]);
}

Port* Block::getOutputPort(int index)
{

	//cout << "Block::getOutputPort\n";
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

	return blockID;
}

void Block::setID(int ID)
{
	blockID = ID;

}

void Block::setPorts()
{

	for (vector<Port>::iterator it = inputPorts.begin(); it != inputPorts.end(); ++it) 
	{
		(*it).setOwnerBlock(this);
	}


	for (vector<Port>::iterator it = outputPorts.begin(); it != outputPorts.end(); ++it) 
	{
		(*it).setOwnerBlock(this);
	}
}

/*Block::~Block()
{
}
*/

QString Block::printPorts()
{
    QString result = "Input:\n";
    for(Port port : this->getInputPorts())
    {
        result.append(port.printConnection()+"\n");
    }

    result.append("\nOutput:\n");
    for(Port port : this->getOutputPorts())
    {
        result.append(port.printConnection()+"\n");
    }

    return result.trimmed();
}
