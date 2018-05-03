#ifndef SCHEME_H
#define SCHEME_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>
#include <algorithm>
#include "blockArithmetic.h"
#include "blockLogic.h"

using namespace std;
class Scheme
{
	public:
		Scheme();
		//~Scheme();
		int createBlock(int blockType);
		void destroyBlock(int ID);
		void run();
		Block* getBlock(int ID);
		Block* step(Block* expectedNextBlock);
		Block* findNonDependentBlock(Block* block);
		bool addBlock(Block* block);
		//testValues();
		//addBlock();		
	private:
		int existingBlocks = 0;
		int createdBlocks = 0;
		vector<Block*> notExecutedBlocks;
		vector<Block*> blockScheme;
};

#endif // SCHEME_H
