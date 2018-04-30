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
class BlockArithmetic : public Block
{
	public:
		BlockArithmetic();	
};

class BlockAdd : public BlockArithmetic
{
	public:
		void executeSpecific();
};

class BlockMul : public BlockArithmetic
{
	public:
		void executeSpecific();
};

class BlockDiv : public BlockArithmetic
{
	public:
		void executeSpecific();
};

class BlockSub : public BlockArithmetic
{
	public:
		void executeSpecific();
};

#endif // ARITHMETIC_H
