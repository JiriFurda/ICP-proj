#include "scheme.h"

//ADD 100
//MUL 101
//DIV 102
//SUB 103
//AND 104
//OR 105
//XOR 106
//NOT 107

Scheme::Scheme(string declaredName)
{
	name = declaredName;	
}

bool Scheme::addBlock(Block* block)
{
	if (block == NULL)
	{
		cerr << "Scheme::addBlock: Attempt to add NULL Block";
		return false;
	}

	blockScheme.push_back(block);
	return true;	
}

bool Scheme::run()
{
	do 
	{
		bool runStepOk = runStep();
	
		if(!runStepOk)
			return false;
	
	} while(!finished);

	return true;
 
}

bool Scheme::runStep()
{

	if (finished)
	{
		cerr << "Scheme::runStep(): Scheme already finished executing\n";
		return false;
	}

	if (!readOnly)
	{
		bool preRunOk = preRun();
		if(!preRunOk)
			return false;
	}

	if(expectedNextBlock == NULL)
		expectedNextBlock = notExecutedBlocks[0];

	expectedNextBlock = step_internal(expectedNextBlock);	

	if (expectedNextBlock == Scheme::LoopDetected)
		return false;

	if (notExecutedBlocks.empty())
		finished = true;

	return true;

}

bool Scheme::preRun()
{
	if (finished)
	{
		cerr << "Scheme::preRun(): Can't run scheme twice";
		return false;
	}

	readOnly = true;

	searchUserDependentBlocks();

	notExecutedBlocks = blockScheme;

	expectedNextBlock = NULL;

	return true;
	

}

Block* Scheme::step_internal(Block* SIexpectedNextBlock)
{
	Block* realNextBlock = findNonDependentBlock(SIexpectedNextBlock);

	if (realNextBlock == Scheme::LoopDetected)
	{
		return Scheme::LoopDetected;
	}
	
	realNextBlock->execute();
	notExecutedBlocks.erase(std::remove(notExecutedBlocks.begin(), notExecutedBlocks.end(), realNextBlock), notExecutedBlocks.end());

	if (realNextBlock->getOutputPorts().size() != 0)
	{
		if (realNextBlock->getOutputPort(0)->getConnectedPort() != NULL)
			return realNextBlock->getOutputPort(0)->getConnectedPort()->getOwnerBlock();
	}
	
	return NULL;
}

void Scheme::searchUserDependentBlocks()
{

	for (Block* block : blockScheme)
	{
		for (Port port : block->getInputPorts())
		{
			if (port.getConnectedPort() == NULL)
			{
				for (string name : port.getNames())
				{
					double value = port.getValue(name);
					if (value != value) //is value NaN ... value != value is true if value is NaN
					{
						cerr << "Scheme::searchUserDependentBlocks()\n";
						port.setValue(name, 420);
					}
					
				}

			}
		}

	}

}



/*void Scheme::run()
{
	notExecutedBlocks = blockScheme;
	Block* expectedNextBlock = NULL;
	
	while(!notExecutedBlocks.empty())
	{
		if(expectedNextBlock == NULL)
			expectedNextBlock = notExecutedBlocks[0];
		
		expectedNextBlock = step(expectedNextBlock);
	}

}*/

/*Block* Scheme::step(Block* expectedNextBlock)
{
	Block* realNextBlock = findNonDependentBlock(expectedNextBlock);	

	realNextBlock->execute();
	notExecutedBlocks.erase(std::remove(notExecutedBlocks.begin(), notExecutedBlocks.end(), realNextBlock), notExecutedBlocks.end());
	if (realNextBlock->getOutputPorts().size() != 0)
	{
		if (realNextBlock->getOutputPort(0)->getConnectedPort() != NULL)
			return realNextBlock->getOutputPort(0)->getConnectedPort()->getOwnerBlock();
	}

	return NULL;

}*/

Block* Scheme::findNonDependentBlock(Block* block)
{
	loopDetectionTrace.clear();

	return findNonDependentBlock_private(block);
}




Block* Scheme::findNonDependentBlock_private(Block* block)
{

	if(std::find(loopDetectionTrace.begin(), loopDetectionTrace.end(), block) != loopDetectionTrace.end())
		return Scheme::LoopDetected;
	else
		loopDetectionTrace.push_back(block);
		
	

	//TODO loop detection

	vector<Port> inputPorts = block->getInputPorts();

	for (vector<Port>::iterator it = inputPorts.begin(); it != inputPorts.end(); ++it)
	{

		Port* connectedPort = it->getConnectedPort();

		if (connectedPort == NULL)
		{
			continue;
			//TODO needed?
		} 

		else
		{	
			if (connectedPort->getOwnerBlock()->wasExecuted() == false)
			{
				return findNonDependentBlock_private(connectedPort->getOwnerBlock());

			}
		}
	}

	return block;
}


void testAdvanced();
void testLoop();

int main()
{
}

void testLoop()
{
	Scheme* myScheme = new Scheme("test");
	Block* blockA = new BlockAdd;
	Block* blockB = new BlockSub;
	
	myScheme->addBlock(blockA);
	myScheme->addBlock(blockB);

	blockA->getInputPort(0)->setConnectedPort(blockB->getOutputPort(0));
	blockA->getInputPort(1)->setValue("float", 1);
	
	blockB->getInputPort(0)->setConnectedPort(blockA->getOutputPort(0));
	blockA->getInputPort(1)->setValue("float", 1);

	if(!myScheme->run())
		cout << "testLoop(): OK!\n";
	else
		cout << "testLoop(): NotOK!\n";
}

void testAdvanced()
{
	BlockAdd* blockA = new BlockAdd;
	BlockSub* blockB = new BlockSub;
	BlockMul* blockC = new BlockMul;
	BlockDiv* blockD = new BlockDiv;
	BlockAdd* blockE = new BlockAdd;
	BlockSub* blockF = new BlockSub;
	BlockMul* blockG = new BlockMul;

	Scheme* myScheme = new Scheme("test");

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



/*	cout << "blockA: " << blockA->getInputPort(0)->getOwnerBlock() << "\n";
	cout << "blockB: " << blockB->getInputPort(0)->getOwnerBlock() << "\n";
	cout << "blockC: " << blockC->getInputPort(0)->getOwnerBlock() << "\n";
	cout << "blockD: " << blockD->getInputPort(0)->getOwnerBlock() << "\n";
	cout << "blockE: " << blockE->getInputPort(0)->getOwnerBlock() << "\n";
	cout << "blockF: " << blockF->getInputPort(0)->getOwnerBlock() << "\n";
	cout << "blockG: " << blockG->getInputPort(0)->getOwnerBlock() << "\n";*/
	
	myScheme->run();

	cout << "blockA result: " << blockA->getOutputPort(0)->getValue("float") << "\n";
	cout << "blockB result: " << blockB->getOutputPort(0)->getValue("float") << "\n";
	cout << "blockC result: " << blockC->getOutputPort(0)->getValue("float") << "\n";
	cout << "blockD result: " << blockD->getOutputPort(0)->getValue("float") << "\n";
	cout << "blockE result: " << blockE->getOutputPort(0)->getValue("float") << "\n";
	cout << "blockF result: " << blockF->getOutputPort(0)->getValue("float") << "\n";
	cout << "blockG result: " << blockG->getOutputPort(0)->getValue("float") << "\n";
}