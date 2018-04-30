#include "blockArithmetic.h"


BlockArithmetic::BlockArithmetic()
	: Block(vector<Port> {Port("float"), Port("float")}, Port("float")){};
		
void BlockAdd::executeSpecific()
{
	getOutputPort(0).setValue(
		"float", getInputPort(0).getValue("float") + getInputPort(1).getValue("float"));
}

void BlockMul::executeSpecific()
{
	getOutputPort(0).setValue(
		"float", getInputPort(0).getValue("float") * getInputPort(1).getValue("float"));
}

void BlockDiv::executeSpecific()
{
	getOutputPort(0).setValue(
		"float", getInputPort(0).getValue("float") / getInputPort(1).getValue("float"));
}

void BlockSub::executeSpecific()
{
	getOutputPort(0).setValue(
		"float", getInputPort(0).getValue("float") - getInputPort(1).getValue("float"));
}
