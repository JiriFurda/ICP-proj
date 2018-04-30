#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>
#include <algorithm> 
#include "port.h"

using namespace std;
class Block
{
	public:
		Block(vector<Port> in, vector<Port> out);
		Block(Port in, Port out);
		Block(vector<Port> in, Port out);
		Block(Port in, vector<Port> out);
		void execute();
		virtual void executeSpecific() = 0;
		Port getInputPort(int index);
		Port getOutputPort(int index);

	private:
		vector<Port> inputPorts;
		vector<Port> outputPorts;
		bool executed = false;
};


#endif // BLOCK_H
