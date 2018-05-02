#include "scheme.h"


//ADD 100
//MUL 101
//DIV 102
//SUB 103
//AND 104
//OR 105
//XOR 106
//NOT 107

Scheme::Scheme()
{
}

Scheme::~Scheme()
{
	for (Block* block : blockScheme)
		delete block;

}

int Scheme::createBlock(int blockType)
{
	cout << "Scheme::createBlock\n";
	switch(blockType)
	{
		case 100:
			blockScheme.push_back(new BlockAdd());
			
			cout << "0\n";
			break;
		case 101:
			blockScheme.push_back(new BlockMul());
			break;

		case 102:
			blockScheme.push_back(new BlockDiv());
			break;

		case 103:
			blockScheme.push_back(new BlockSub());
			break;

		case 104:
			blockScheme.push_back(new BlockAnd());
			break;

		case 105:
			blockScheme.push_back(new BlockOr());
			break;
		case 106:
			blockScheme.push_back(new BlockXor());
			break;

		case 107:
			blockScheme.push_back(new BlockNot());
			break;

	}
	cout << "1\n";
	blockScheme[existingBlocks]->setID(createdBlocks);
	cout << "2\n";
	existingBlocks += 1;
	createdBlocks +=1;
	return createdBlocks-1;
	
}

/*Block* Scheme::getBlock(int ID)
{
	for (Block* block : blockScheme)
	{
		if (block->getID() == ID)
			return 
	}

	existingBlocks -= 1;
}

void Scheme::destroyBlock(int ID)
{
	erase(myvector.begin() + getblock(ID));		

}*/

int main()
{
	BlockAdd blockA;
	BlockAdd blockB;

	blockA.getInputPort(0)->setValue("float",6);
	blockA.getInputPort(1)->setValue("float",12);
	blockA.executeSpecific();
	cout << blockA.getOutputPort(0)->getValue("float") << "\n";

	blockA.getOutputPort(0)->setConnectedPort(blockB.getInputPort(0));

	blockB.getInputPort(1)->setValue("float",2);

	

	
	
/*	Scheme myScheme;
	myScheme.createBlock(ADD);
	myScheme.createBlock(MUL);
	myScheme.createBlock(DIV);
	myScheme.createBlock(SUB);
	
	


	myScheme.createBlock(AND);
	myScheme.createBlock(OR);
	myScheme.createBlock(XOR);
	myScheme.createBlock(NOT);*/
}
