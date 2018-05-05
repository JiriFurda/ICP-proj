#ifndef BLOCKCOMPLEX_H
#define BLOCKCOMPLEX_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>
#include <algorithm>
#include "port.h"
#include "block.h"


using namespace std;
class BlockComplex : public Block
{
    public:
        BlockComplex();
};

class BlockCxAdd : public BlockComplex
{
    public:
        void executeSpecific();
};

class BlockCxMul : public BlockComplex
{
    public:
        void executeSpecific();
};

class BlockCxDiv : public BlockComplex
{
    public:
        void executeSpecific();
};

class BlockCxSub : public BlockComplex
{
    public:
        void executeSpecific();
};


#endif // BLOCKCOMPLEX_H
