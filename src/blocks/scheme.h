/**
 * Backend representation of scheme.
 * @brief Header file for Scheme
 * @file scheme.h
 * @author Peter Havan (xhavan00)
 * @author Jiri Furda (xfurda00)
 */


#ifndef SCHEME_H
#define SCHEME_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>
#include <algorithm>
#include "block.h"
#include "blockArithmetic.h"
#include "blockComplex.h"
#include "blockLogic.h"

#include <QString>
#include <QInputDialog>
#include <QMessageBox>

using namespace std;



/**
 * @brief The Scheme class is backend representation of scheme and contains its interface.
 */
class Scheme
{
	public:
        /**
         * @brief Constructor of class Scheme.
         * @param declaredName  Name of the Scheme.
         */
		Scheme(string declaredName);

        /**
         * @brief run executes whole Scheme
         * @return True when successful, false when not
         */
		bool run();

        /**
         * @brief addBlock adds new block to the Scheme
         * @param block Pointer to created block
         * @return True when successful, false when not
         */
		bool addBlock(Block* block);	

        /**
         * @brief runStep executes one step of the Scheme
         * @param highlight determines if executed block should be highlighted (stepping mode)
         * @return True when successful, false when not
         */
        bool runStep(bool highlight);

        /**
         * @brief revert reverts Scheme to pre-execute state.
         */
        void revert();

	private:
        Block* searchUserDependentBlocks();
        Block* step_internal(Block* SIexpectedNextBlock, bool highlight);
        bool preRun();
        Block* findNonDependentBlock(Block* block);
        bool removeBlock(Block* block);
		Block* findNonDependentBlock_private(Block* block);

		Block* LoopDetected = new BlockAdd();
		string name;
		bool readOnly = false;
		bool finished = false;
		int existingBlocks = 0;
		int createdBlocks = 0;
		vector<Block*> notExecutedBlocks;
		vector<Block*> blockScheme;
		vector<Block*> loopDetectionTrace;
		Block* expectedNextBlock = NULL;
};

#endif // SCHEME_H
