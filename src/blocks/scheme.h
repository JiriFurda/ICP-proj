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
		~Scheme();
		int createBlock(int blockType);
		void destroyBlock(int ID);
		void evalScheme();
		Block* getBlock(int ID);
		//testValues();
		//addBlock();		
	private:
		int existingBlocks = 0;
		int createdBlocks = 0;
		vector<Block*> blockScheme;
};

#endif // SCHEME_H
