/**
 * Backend representation of block.
 * @brief Header file for Block
 * @file block.h
 * @author Peter Havan (xhavan00)
 * @author Jiri Furda (xfurda00)
 */

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



/**
 * @brief The Block class is backend representation of block and contains its interface.
 * This class is parent of all the block types used.
 */
class Block
{
	public:
        /**
         * @brief Main constructor for this class.
         * @param in    Pointer to vector of input Port objects.
         * @param out   Pointer to vector of output Port objects.
         */
		Block(const vector<Port>& in, const vector<Port>& out);

        /**
         * @brief Secondary overloaded constructor for this class.
         * @param in    Pointer to input Port object.
         * @param out   Pointer to output Port object.
         */
		Block(const Port& in, const Port& out);

        /**
         * @brief Secondary overloaded constructor for this class.
         * @param in    Pointer to vector of input Port objects.
         * @param out   Pointer to output Port object.
         */
		Block(const vector<Port>& in, const Port& out);

        /**
         * @brief Secondary overloaded constructor for this class.
         * @param in    Pointer to input Port object.
         * @param out   Pointer to vector of input Port objects.
         */
		Block(const Port& in, const vector<Port>& out);

        /**
         * @brief execute is general method realizing pre-execute setting and
         * then executing block type specific calculation using executeSpecific().
         */
		void execute();

        /**
         * @brief executeSpecific is virtual method replaced in block type specific classes.
         * It realizes block type specific calculation.
         */
        virtual void executeSpecific() = 0;

        /**
         * @brief getInputPort is method returning pointer to input Port at specific index.
         * @param index Index specifying required port.
         * @return Pointer to input Port at specific index.
         */
		Port* getInputPort(int index);

        /**
         * @brief getOutputPort is method returning pointer to output Port at specific index.
         * @param index Index specifying required port.
         * @return Pointer to output Port at specific index.
         */
		Port* getOutputPort(int index);

        virtual ~Block() {};    /// @brief Destructor of this class.
        void setPorts();    /// @brief setPorts is method that sets ownerBlock to every Port owned by the block.
        vector<Port>getInputPorts();    /// @brief getInputPorts is method returning vector of the block's input Ports.
        vector<Port>getOutputPorts();   /// @brief getInputPorts is method returning vector of the block's output Ports.
        bool wasExecuted(); /// @brief wasExecuted is method returning bool value indicating if the block was already executed.
        QString printPorts();   /// @brief printPorts is method used by GUI to print the block's Ports and it's values.
        vector<Port> inputPorts;    /// @brief Vector containing the block's input Ports
        void linkGUIobject(BlockGraphicItem *GUIobject);    /// @brief linkGUIobject is method used by GUI to link the backend block to GUI block.
        BlockGraphicItem *GUIobject;    /// @brief Pointer to GUI block.
        bool deleted;   /// @brief Bool value indicating if this block was removed from the scheme.

    protected:

	private:
		vector<Port> outputPorts;
		bool executed = false;
};


#endif // BLOCK_H
