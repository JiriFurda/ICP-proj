#include "block.h"

using namespace std;

Block::Block(vector<Port> in, vector<Port> out)
{
	inputPorts = in;
	outputPorts = out;
}

Block::Block(Port in, Port out)
{
	inputPorts.push_back(in);
	outputPorts.push_back(out);
}

Block::Block(vector<Port> in, Port out)
{
	cout << "Block::Block\n";
	inputPorts = in;
	outputPorts.push_back(out);
	cout << "Block::Block\n";
}

Block::Block(Port in, vector<Port> out)
{
	inputPorts.push_back(in);
	outputPorts = out;
}

void Block::execute()
{
	if (executed)
	{
		cerr << "Block::execute(): Found loop\n";
		exit(-1);
	}

	executeSpecific();
	executed = true;
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

int Block::getID()
{
	return blockID;
}

void Block::setID(int ID)
{
	blockID = ID;
}

/*Block::~Block()
{
}
*/
