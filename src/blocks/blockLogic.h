/**
 * Backend representation of logic blocks.
 * @brief Header file for Block classes from group "Logic"
 * @file blockLogic.h
 * @author Peter Havan (xhavan00)
 * @author Jiri Furda (xfurda00)
 */

#ifndef BLOCK_LOGIC_H
#define BLOCK_LOGIC_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>
#include <algorithm> 
#include "port.h"
#include "block.h"

using namespace std;


/**
 * @brief The BlockLogic class is virtual class containing constructor for Block classes from group "Logic".
 */
class BlockLogic : public Block
{
	public:
        BlockLogic();  /// Constructor for Block classes from group "Logic".
};

/**
 * @brief The BlockAnd class is Block realising logical conjuction of two bool values.
 */
class BlockAnd : public BlockLogic
{
	public:
        void executeSpecific(); /// @brief executeSpecific realises logical conjuction of two bool values from input Ports and saves it to output Port
};

/**
 * @brief The BlockOr class is Block realising logical disjuction of two bool values.
 */
class BlockOr : public BlockLogic
{
	public:
        void executeSpecific(); /// @brief executeSpecific realises logical disjuction of two bool values from input Ports and saves it to output Port
};

/**
 * @brief The BlockXor class is Block realising exclusive logical disjuction of two bool values.
 */
class BlockXor : public BlockLogic
{
	public:
        void executeSpecific(); /// @brief executeSpecific realises exclusive logical disjuction of two bool values from input Ports and saves it to output Port
};

/**
 * @brief double2bool is method converting double value to bool value.
 * @param value Double to be converted.
 * @return Converted bool value.
 */
bool double2bool(double value);

/**
 * @brief bool2double is method converting bool value to double value.
 * @param value Bool to be converted.
 * @return Converted double value.
 */
double bool2double(bool value);

#endif // LOGIC_H
