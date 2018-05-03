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
		Scheme(string declaredName);
		int createBlock(int blockType);
		void destroyBlock(int ID);
		bool run();
		Block* getBlock(int ID);
		Block* step(Block* expectedNextBlock);
		Block* findNonDependentBlock(Block* block);
		bool addBlock(Block* block);	
		void searchUserDependentBlocks();
		Block* step_internal(Block* SIexpectedNextBlock);
		bool preRun();
		bool runStep();
	private:
		Block* findNonDependentBlock_private(Block* block);

		Block* LoopDetected = new BlockAdd();
		string name;
		bool readOnly = false;
		bool finished = false;
		int existingBlocks = 0;
		int createdBlocks = 0;
		vector<Block*> notExecutedBlocks;
		vector<Block*> blockScheme;
		vector<Block*> loopDetectionTrace;
		Block* expectedNextBlock = NULL;
};

#endif // SCHEME_H
