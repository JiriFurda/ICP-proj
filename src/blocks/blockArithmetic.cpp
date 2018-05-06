/**
 * Backend representation of arithmetic blocks.
 * @brief Header file for Block classes from group "Arithmetic"
 * @file blockArithmetic.cpp
 * @author Peter Havan (xhavan00)
 * @author Jiri Furda (xfurda00)
 */

#include "blockArithmetic.h"
#include "port.h"
#include "block.h"


BlockArithmetic::BlockArithmetic()
	: Block(vector<Port> {Port("float", false), Port("float", false)}, Port("float", true)){};
		
void BlockAdd::executeSpecific()
{
	getOutputPort(0)->setValue(
		"float", getInputPort(0)->getValue("float") + getInputPort(1)->getValue("float"));
}

void BlockMul::executeSpecific()
{
	getOutputPort(0)->setValue(
		"float", getInputPort(0)->getValue("float") * getInputPort(1)->getValue("float"));
}

void BlockDiv::executeSpecific()
{
	getOutputPort(0)->setValue(
		"float", getInputPort(0)->getValue("float") / getInputPort(1)->getValue("float"));
}

void BlockSub::executeSpecific()
{
	getOutputPort(0)->setValue(
		"float", getInputPort(0)->getValue("float") - getInputPort(1)->getValue("float"));
}
