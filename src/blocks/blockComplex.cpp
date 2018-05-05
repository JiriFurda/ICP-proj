#include "blockComplex.h"

BlockComplex::BlockComplex()
    : Block(vector<Port> {Port(vector<string>{"real", "imaginary"}, false), Port(vector<string>{"real", "imaginary"}, false)},
            Port(vector<string>{"real", "imaginary"}, true)){};

void BlockCxAdd::executeSpecific()
{
    for(string name : vector<string>{"real","imaginary"})
    {
        this->getOutputPort(0)->setValue(name,
            this->getInputPort(0)->getValue(name) + this->getInputPort(1)->getValue(name));
    }
}

void BlockCxSub::executeSpecific()
{
    for(string name : vector<string>{"real","imaginary"})
    {
        this->getOutputPort(0)->setValue(name,
            this->getInputPort(0)->getValue(name) - this->getInputPort(1)->getValue(name));
    }
}


void BlockCxMul::executeSpecific()
{
    double x_re = this->getInputPort(0)->getValue("real");
    double x_im = this->getInputPort(0)->getValue("imaginary");
    double y_re = this->getInputPort(1)->getValue("real");
    double y_im = this->getInputPort(1)->getValue("imaginary");

    this->getOutputPort(0)->setValue("real",
            (x_re * y_re) - (x_im * y_im));
    this->getOutputPort(0)->setValue("imaginary",
            (x_re * y_im) + (y_re * x_im));
}

void BlockCxDiv::executeSpecific()
{
    double x_re = this->getInputPort(0)->getValue("real");
    double x_im = this->getInputPort(0)->getValue("imaginary");
    double y_re = this->getInputPort(1)->getValue("real");
    double y_im = this->getInputPort(1)->getValue("imaginary");

    this->getOutputPort(0)->setValue("real",
            ((x_re * y_re) + (x_im * y_im)) / (pow(y_re, 2) + pow(y_im, 2)));
    this->getOutputPort(0)->setValue("imaginary",
            (-(x_re * y_im) + (x_im * y_re)) / (pow(y_re, 2) + pow(y_im, 2)));
}


