#ifndef BLOCK_LOGIC_H
#define BLOCK_LOGIC_H

#define AND 104
#define OR 105
#define XOR 106
#define NOT 107

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>
#include <algorithm> 
#include "port.h"
#include "block.h"


using namespace std;
class BlockLogic : public Block
{
	public:
		BlockLogic();	
};

class BlockAnd : public BlockLogic
{
	public:
		void executeSpecific();
};

class BlockOr : public BlockLogic
{
	public:
		void executeSpecific();
};

class BlockXor : public BlockLogic
{
	public:
		void executeSpecific();
};

class BlockNot : public BlockLogic
{
	public:
		void executeSpecific();
};

bool double2bool(double value);
double bool2double(bool value);

#endif // LOGIC_H
