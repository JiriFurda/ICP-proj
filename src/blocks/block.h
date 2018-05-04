#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>
#include <algorithm> 

#include <QString>
#include "gui/blockgraphicitem.h"

class Port;

using namespace std;
class Block
{
	public:
		Block(const vector<Port>& in, const vector<Port>& out);
		Block(const Port& in, const Port& out);
		Block(const vector<Port>& in, const Port& out);
		Block(const Port& in, const vector<Port>& out);
		void execute();
		virtual void executeSpecific() = 0;
		Port* getInputPort(int index);
		Port* getOutputPort(int index);
		int getID();
		void setID(int ID);
		virtual ~Block() {};
		void setPorts();
		vector<Port>getInputPorts();
		vector<Port>getOutputPorts();
		bool wasExecuted();
        QString printPorts();
        vector<Port> inputPorts;
        void linkGUIobject(BlockGraphicItem *GUIobject);
        BlockGraphicItem *GUIobject;

	private:
		int blockID;
		vector<Port> outputPorts;
		bool executed = false;
};


#endif // BLOCK_H
