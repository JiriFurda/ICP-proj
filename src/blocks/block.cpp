/**
 * Backend representation of block.
 * @brief Source file for Block
 * @file block.cpp
 * @author Peter Havan (xhavan00)
 * @author Jiri Furda (xfurda00)
 */

#include "block.h"
#include "port.h"

using namespace std;

Block::Block(const vector<Port>& in, const vector<Port>& out)
{
	inputPorts = in;
	outputPorts = out;
	setPorts();
    this->GUIobject = NULL;
    this->deleted = false;
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

	executeSpecific();
	executed = true;
}

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

    return result.trimmed();    // Remove last \n
}

void Block::linkGUIobject(BlockGraphicItem *GUIobject)
{
    this->GUIobject = GUIobject;
}
