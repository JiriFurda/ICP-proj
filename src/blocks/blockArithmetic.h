/**
 * Backend representation of arithmetic blocks.
 * @brief Header file for Block classes from group "Arithmetic"
 * @file blockArithmetic.h
 * @author Peter Havan (xhavan00)
 * @author Jiri Furda (xfurda00)
 */

#ifndef BLOCK_ARITHMETIC_H
#define BLOCK_ARITHMETIC_H

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
 * @brief The BlockArithmetic class is virtual class containing constructor for Block classes from group "Arithmetic"
 */
class BlockArithmetic : public Block
{
	public:
        BlockArithmetic();  ///	Constructor for Block classes from group "Arithmetic"
};

/**
 * @brief The BlockAdd class is Block adding two float numbers
 */
class BlockAdd : public BlockArithmetic
{
	public:
        void executeSpecific(); /// @brief executeSpecific adds two float values from input Ports and saves it to output Port
};

/**
 * @brief The BlockMul class is Block multipling two float numbers
 */
class BlockMul : public BlockArithmetic
{
	public:
        void executeSpecific(); /// @brief executeSpecific mutliplies two float values from input Ports and saves it to output Port
};

/**
 * @brief The BlockDiv class is Block dividing two float numbers
 */
class BlockDiv : public BlockArithmetic
{
	public:
        void executeSpecific(); /// @brief executeSpecific divides two float values from input Ports and saves it to output Port
};

/**
 * @brief The BlockSub class is Block substracting two float numbers
 */
class BlockSub : public BlockArithmetic
{
	public:
        void executeSpecific(); /// @brief executeSpecific substracts two float values from input Ports and saves it to output Port
};

#endif // ARITHMETIC_H
