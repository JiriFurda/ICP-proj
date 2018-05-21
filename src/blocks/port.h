/**
 * Backend representation of port.
 * @brief Header file for Port
 * @file port.h
 * @author Peter Havan (xhavan00)
 * @author Jiri Furda (xfurda00)
 */

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


/**
 * @brief The Port class is backend representation of port and contains its interface.
 */
class Port
{
	public:
        /**
         * @brief Constructor of class Port with value type consisting of only one part.
         * @param name  Name of value type.
         * @param declaredType  False for output, true for input.
         */
		Port(string name, bool declaredType);

        /**
         * @brief Constructor of class Port with value type consisting of more than one part.
         * @param name  Array of value type names.
         * @param declaredType  False for output, true for input.
         */
		Port(vector<string> arrayOfNames, bool declaredType);

        /**
         * @brief compatible is method determining if this and other Port are compatibile for connection.
         * @param other Port to connect to.
         * @return True when compatibile, false when not.
         */
		bool compatible(Port other);

        /**
         * @brief setValue is method used to set value with specified name of the Port.
         * @param name  Name of value type to be set.
         * @param value Value to be set.
         * @return True when successful, false when not.
         */
		bool setValue(string name, double value);

        /**
         * @brief getValue is method used to get value with specified name of the Port.
         * @param name  Name of desired value type.
         * @return  Desired value.
         */
		double getValue(string name);

        /**
         * @brief getValue is method used to get map of both value and its name with specified name of the Port.
         * @return  Map of values and names of this Port.
         */
		map<string, double> getContent();

        /**
         * @brief getNames is method used to get vector of value type names of this Port
         * @return Vector of value type names of this Port
         */
		vector<string> getNames();

        /**
         * @brief setConnectedPort is method used to set connected Port to this Port
         * @param other Other Port this Ports is connected to
         * @return True when successful, false when not
         */
		bool setConnectedPort(Port* other);

        /**
         * @brief getConnectedPort is method returning pointer of Port connected to this Port
         * @return Pointer of Port connected to this Port or NULL if none Port is connected
         */
		Port* getConnectedPort();

        /**
         * @brief getOwnerBlock is method returting pointer of Block that owns this Port
         * @return Pointer of Block that owns this Port
         */
		Block* getOwnerBlock();

        /**
         * @brief setOwnerBlock is method that sets owner Block of this Port
         * @param otherBlock Pointer of owner Block
         */
		void setOwnerBlock(Block* otherBlock);

        /**
         * @brief print is method used by GUI to get informations about this Port
         * @return QString containing informations about this Port
         */
        QString print();

        /**
         * @brief printConnection is method used by GUI to get informations and value about connection of Port
         * @return QString containing informations and value about connection of Port
         */
        QString printConnection();

        /**
         * @brief isInputType is method used to determine if this Port is input
         * @return True if Port is input type, false when not
         */
        bool isInputType();

        /**
         * @brief isOutputType is method used to determine if this Port is output
         * @return True if Port is output type, false when not
         */
        bool isOutputType();

        /**
         * @brief reset is method used to reset values to default on this Port
         */
        void reset();

	protected:
		map<string, double> content;
	private:
		bool type;
		Port* connectedPort = NULL;
		Block* ownerBlock = NULL;
};


#endif // PORT_H
