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

/*Scheme::~Scheme()
{
	for (Block* block : blockScheme)
		delete block;

}*/

/*int Scheme::createBlock(int blockType)
{
	////cout << "Scheme::createBlock\n";
	switch(blockType)
	{
		case ADD:
			blockScheme.push_back(new BlockAdd());
			
			//cout << "0\n";
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
	////cout << "1\n";
	blockScheme[existingBlocks]->setID(createdBlocks);
	////cout << blockScheme[existingBlocks]->getID() << "\n";
	////cout << "2\n";
	existingBlocks += 1;
	createdBlocks +=1;
	return createdBlocks-1;
	
}*/

bool Scheme::addBlock(Block* block)
{
	if (block == NULL)
	{
		//cout << "Scheme::addBlock: Attempt to add NULL Block";
		return false;
	}

	blockScheme.push_back(block);
	return true;	
}

void Scheme::run()
{
	notExecutedBlocks = blockScheme;
	Block* expectedNextBlock = NULL;
	
	while(!notExecutedBlocks.empty())
	{
		if(expectedNextBlock == NULL)
			expectedNextBlock = notExecutedBlocks[0];
		
		expectedNextBlock = step(expectedNextBlock);
	}

}

Block* Scheme::step(Block* expectedNextBlock)
{
	cout << "Scheme::step " << expectedNextBlock << "\n";
	Block* realNextBlock = findNonDependentBlock(expectedNextBlock);	

	realNextBlock->execute();
	notExecutedBlocks.erase(std::remove(notExecutedBlocks.begin(), notExecutedBlocks.end(), realNextBlock), notExecutedBlocks.end());

	if (realNextBlock->getOutputPorts().size() != 0)
	{
		if (realNextBlock->getOutputPort(0)->getConnectedPort() != NULL)
			return realNextBlock->getOutputPort(0)->getConnectedPort()->getOwnerBlock();
	}

	return NULL;

}

Block* Scheme::findNonDependentBlock(Block* block)
{
	cout << "Scheme::findNonDependentBlock" << block << "\n";

	for (vector<Port>::iterator it = block->getInputPorts().begin(); it != block->getInputPorts().end(); ++it) 
	{
		cout << "haha\n";
		Port* connectedPort = it->getConnectedPort();
		cout << connectedPort << "\n";
		cout << "hihi\n";
		if (connectedPort == NULL)
		{
		//	continue;
			//TODO needed?
		} 

		else
		{	
			cout << "hehe\n";
			if (connectedPort->getOwnerBlock()->wasExecuted() == false)
			{
				return findNonDependentBlock(connectedPort->getOwnerBlock());

			}
		
		}
	
	}

	return block;
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


	
	BlockAdd* blockA = new BlockAdd;
	BlockSub* blockB = new BlockSub;
	BlockMul* blockC = new BlockMul;
	BlockDiv* blockD = new BlockDiv;
	BlockAdd* blockE = new BlockAdd;
	BlockSub* blockF = new BlockSub;
	BlockMul* blockG = new BlockMul;

	Scheme* myScheme = new Scheme;

	myScheme->addBlock(blockD);
	myScheme->addBlock(blockF);
	myScheme->addBlock(blockG);
	myScheme->addBlock(blockB);
        myScheme->addBlock(blockE);
        myScheme->addBlock(blockC);
	myScheme->addBlock(blockA);	


	blockA->getInputPort(0)->setConnectedPort(blockB->getOutputPort(0));
	blockA->getInputPort(1)->setConnectedPort(blockC->getOutputPort(0));

       
	blockB->getInputPort(0)->setConnectedPort(blockD->getOutputPort(0));
	blockB->getInputPort(1)->setConnectedPort(blockE->getOutputPort(0));

	blockC->getInputPort(0)->setConnectedPort(blockF->getOutputPort(0));
        blockC->getInputPort(1)->setValue("float", 8);  
 
	blockD->getInputPort(0)->setValue("float", 3);
	blockD->getInputPort(1)->setValue("float", 4); 
      
	blockE->getInputPort(0)->setValue("float", 5);  
	blockE->getInputPort(1)->setConnectedPort(blockG->getOutputPort(0)); 
	
	blockF->getInputPort(0)->setValue("float", 6);  
	blockF->getInputPort(1)->setValue("float", 7); 
	
	blockG->getInputPort(0)->setValue("float", 1);  
	blockG->getInputPort(1)->setValue("float", 2);

/*	BlockAdd blockA;
	BlockSub blockB;
	BlockMul blockC;
	BlockDiv blockD;
	BlockAdd blockE;
	BlockSub blockF;
	BlockMul blockG;

	Scheme myScheme;

	myScheme.addBlock(&blockD);
	myScheme.addBlock(&blockF);
	myScheme.addBlock(&blockG);
	myScheme.addBlock(&blockB);
        myScheme.addBlock(&blockE);
        myScheme.addBlock(&blockC);
	myScheme.addBlock(&blockA);

	blockA.getInputPort(0)->setConnectedPort(blockB.getOutputPort(0));
	blockA.getInputPort(1)->setConnectedPort(blockC.getOutputPort(0));

	////cout << blockB.getOutputPort(0) << "\n";
       
	blockB.getInputPort(0)->setConnectedPort(blockD.getOutputPort(0));
	blockB.getInputPort(1)->setConnectedPort(blockE.getOutputPort(0));

	blockC.getInputPort(0)->setConnectedPort(blockF.getOutputPort(0));
        blockC.getInputPort(1)->setValue("float", 8);  
 
	blockD.getInputPort(0)->setValue("float", 3);
	blockD.getInputPort(1)->setValue("float", 4); 
      
	blockE.getInputPort(0)->setValue("float", 5);  
	blockE.getInputPort(1)->setConnectedPort(blockG.getOutputPort(0)); 
	
	blockF.getInputPort(0)->setValue("float", 6);  
	blockF.getInputPort(1)->setValue("float", 7); 
	
	blockG.getInputPort(0)->setValue("float", 1);  
	blockG.getInputPort(1)->setValue("float", 2);*/

	/*//cout << "blockA: " << blockA.getInputPort(0)->getOwnerBlock() << "\n";
	//cout << "blockB: " << blockB.getInputPort(0)->getOwnerBlock() << "\n";
	//cout << "blockC: " << blockC.getInputPort(0)->getOwnerBlock() << "\n";
	//cout << "blockD: " << blockD.getInputPort(0)->getOwnerBlock() << "\n";
	//cout << "blockE: " << blockE.getInputPort(0)->getOwnerBlock() << "\n";
	//cout << "blockF: " << blockF.getInputPort(0)->getOwnerBlock() << "\n";
	//cout << "blockG: " << blockG.getInputPort(0)->getOwnerBlock() << "\n";*/
	
	myScheme->run();

	cout << "blockA result: " << blockA->getOutputPort(0)->getValue("float") << "\n";
	cout << "blockB result: " << blockB->getOutputPort(0)->getValue("float") << "\n";
	cout << "blockC result: " << blockC->getOutputPort(0)->getValue("float") << "\n";
	cout << "blockD result: " << blockD->getOutputPort(0)->getValue("float") << "\n";
	cout << "blockE result: " << blockE->getOutputPort(0)->getValue("float") << "\n";
	cout << "blockF result: " << blockF->getOutputPort(0)->getValue("float") << "\n";
	cout << "blockG result: " << blockG->getOutputPort(0)->getValue("float") << "\n";
}
