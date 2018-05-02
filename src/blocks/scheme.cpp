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
	//cout << "Scheme::createBlock\n";
	switch(blockType)
	{
		case ADD:
			blockScheme.push_back(new BlockAdd());
			
			cout << "0\n";
			break;
		case MUL:
			blockScheme.push_back(new BlockMul());
			break;

		case DIV:
			blockScheme.push_back(new BlockDiv());
			break;

		case SUB:
			blockScheme.push_back(new BlockSub());
			break;

		case AND:
			blockScheme.push_back(new BlockAnd());
			break;

		case OR:
			blockScheme.push_back(new BlockOr());
			break;
		case XOR:
			blockScheme.push_back(new BlockXor());
			break;

		case NOT:
			blockScheme.push_back(new BlockNot());
			break;

	}
	//cout << "1\n";
	blockScheme[existingBlocks]->setID(createdBlocks);
	//cout << blockScheme[existingBlocks]->getID() << "\n";
	//cout << "2\n";
	existingBlocks += 1;
	createdBlocks +=1;
	return createdBlocks-1;
	
}

void Scheme::evalScheme()
{


}

/*Block* Scheme::getBlock(int ID)
{
	for (Block* block : blockScheme)
	{
		if (block->getID() == ID)
			return 
	}

}

void Scheme::destroyBlock(int ID)
{
	erase(myvector.begin() + getblock(ID));
	existingBlocks -= 1;
}*/

int main()
{
	BlockAdd blockA;
	BlockAdd blockB;

	blockA.getInputPort(0)->setValue("float",6);
	blockA.getInputPort(1)->setValue("float",12);
	blockA.setID(0);
	blockA.executeSpecific();
	cout << blockA.getOutputPort(0)->getValue("float") << "\n";
	
	//cout << &(blockA) << "\n";
	//cout << blockA.getInputPort(0)->getOwnerBlock() << "-----------------------\n";

	cout << blockA.getOutputPort(0)->getOwnerBlock()->getOutputPort(0)->getValue("float") << "\n";

	cout << blockA.getOutputPort(0)->getOwnerBlock()->getID() << "\n";

	blockA.getOutputPort(0)->setConnectedPort(blockB.getInputPort(0));

	blockB.getInputPort(1)->setValue("float",2);

	

	
	
	Scheme myScheme;
	myScheme.createBlock(ADD);
	myScheme.createBlock(MUL);
	myScheme.createBlock(DIV);
	myScheme.createBlock(SUB);
	
	


	myScheme.createBlock(AND);
	myScheme.createBlock(OR);
	myScheme.createBlock(XOR);
	myScheme.createBlock(NOT);
}
