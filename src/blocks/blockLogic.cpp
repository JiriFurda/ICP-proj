/**
 * Backend representation of logic blocks.
 * @brief Source file for Block classes from group "Logic"
 * @file blockLogic.cpp
 * @author Peter Havan (xhavan00)
 * @author Jiri Furda (xfurda00)
 */

#include "blockLogic.h"
#include "port.h"
#include "block.h"


BlockLogic::BlockLogic()
	: Block(vector<Port> {Port("bool", false), Port("bool", false)}, Port("bool", true)){};
		
void BlockAnd::executeSpecific()
{
    bool resultB = double2bool(getInputPort(0)->getValue("bool")) & double2bool(getInputPort(1)->getValue("bool"));
    double resultD = bool2double(resultB);

	getOutputPort(0)->setValue(
		"bool", resultD);
}

void BlockOr::executeSpecific()
{
    bool resultB = double2bool(getInputPort(0)->getValue("bool")) | double2bool(getInputPort(1)->getValue("bool"));
    double resultD = bool2double(resultB);

	getOutputPort(0)->setValue(
		"bool", resultD);
}

void BlockXor::executeSpecific()
{
    bool resultB = double2bool(getInputPort(0)->getValue("bool")) ^ double2bool(getInputPort(1)->getValue("bool"));
    double resultD = bool2double(resultB);

	getOutputPort(0)->setValue(
		"bool", resultD);
}


bool double2bool(double value)
{
    if (value > 0.5)
        return true;
    else
        return false;
}

double bool2double(bool value)
{
    if (value)
        return 1;
    else
        return 0;
}

