/**
 * Backend representation of complex arithmetic blocks.
 * @brief Header file for Block classes from group "Complex arithmetic"
 * @file blockComplex.h
 * @author Peter Havan (xhavan00)
 * @author Jiri Furda (xfurda00)
 */

#ifndef BLOCKCOMPLEX_H
#define BLOCKCOMPLEX_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>
#include <algorithm>
#include <math.h>
#include "port.h"
#include "block.h"

using namespace std;



/**
 * @brief The BlockComplex class is virtual class containing constructor for Block classes from group "Complex arithmetic"
 */
class BlockComplex : public Block
{
    public:
        BlockComplex();  /// Constructor for Block classes from group "Complex arithmetic"
};

/**
 * @brief The BlockCxAdd class is Block multiplying two complex numbers
 */
class BlockCxAdd : public BlockComplex
{
    public:
        void executeSpecific(); /// @brief executeSpecific adds two complex values from input Ports and saves it to output Port
};

/**
 * @brief The BlockCxMul class is Block multipling two complex numbers
 */
class BlockCxMul : public BlockComplex
{
    public:
        void executeSpecific(); /// @brief executeSpecific mutliplies two complex values from input Ports and saves it to output Port
};

/**
 * @brief The BlockCxDiv class is Block dividing two complex numbers
 */
class BlockCxDiv : public BlockComplex
{
    public:
        void executeSpecific(); /// @brief executeSpecific divides two complex values from input Ports and saves it to output Port
};

/**
 * @brief The BlockCxSub class is Block substracting two complex numbers
 */
class BlockCxSub : public BlockComplex
{
    public:
        void executeSpecific(); /// @brief executeSpecific substracts two complex values from input Ports and saves it to output Port
};


#endif // BLOCKCOMPLEX_H
