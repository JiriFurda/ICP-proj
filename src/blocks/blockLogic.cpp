#include "blockLogic.h"


BlockLogic::BlockLogic()
	: Block(vector<Port> {Port("bool"), Port("bool")}, Port("bool")){};
		
void BlockAnd::executeSpecific()
{
	bool resultB = checkBool(getInputPort(0)->getValue("bool")) & checkBool(getInputPort(1)->getValue("bool"));
	double resultD;
	if (resultB)
		resultD = 1.0;
	else
		resultD = -1.0;

	getOutputPort(0)->setValue(
		"bool", resultD);
}

void BlockOr::executeSpecific()
{
	bool resultB = checkBool(getInputPort(0)->getValue("bool")) | checkBool(getInputPort(1)->getValue("bool"));
	double resultD;
	if (resultB)
		resultD = 1.0;
	else
		resultD = -1.0;

	getOutputPort(0)->setValue(
		"bool", resultD);
}

void BlockXor::executeSpecific()
{
	bool resultB = checkBool(getInputPort(0)->getValue("bool")) ^ checkBool(getInputPort(1)->getValue("bool"));
	double resultD;
	if (resultB)
		resultD = 1.0;
	else
		resultD = -1.0;

	getOutputPort(0)->setValue(
		"bool", resultD);
}

void BlockNot::executeSpecific()
{
	bool resultB = checkBool(getInputPort(0)->getValue("bool"));
	double resultD;
	if (!resultB)
		resultD = 1.0;
	else
		resultD = -1.0;

	getOutputPort(0)->setValue(
		"bool", resultD);
}

bool checkBool(double booleanVal)
{
	if (booleanVal > 0)
		return true;
	else
		return false;
}
