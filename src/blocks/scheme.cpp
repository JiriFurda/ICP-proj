/**
 * Backend representation of scheme.
 * @brief Source file for Scheme
 * @file scheme.cpp
 * @author Peter Havan (xhavan00)
 * @author Jiri Furda (xfurda00)
 */


#include "scheme.h"

Scheme::Scheme(string declaredName)
{
	name = declaredName;	
    this->nextId = 1;
}

bool Scheme::addBlock(Block* block)
{
	if (block == NULL)
	{
		cerr << "Scheme::addBlock: Attempt to add NULL Block";
		return false;
	}

	blockScheme.push_back(block);

    block->setId(this->nextId++);

	return true;	
}

bool Scheme::removeBlock(Block* block)
{
    if (block == NULL)
    {
        cerr << "Scheme::removeBlock: Attempt to remove NULL Block";
        return false;
    }

    int index = 0;
    bool found = false;
    for (vector<Block*>::iterator savedBlock = this->blockScheme.begin(); savedBlock != this->blockScheme.end(); ++savedBlock)
    {
        if(block == *savedBlock)
        {
            found = true;
            break;
        }

        index++;
    }
    if (!found)
    {
        cerr << "Scheme::removeBlock: Block wasn't found in scheme";
        return false;
    }

    blockScheme.erase(blockScheme.begin()+index);

    return true;
}

bool Scheme::run()
{
	do 
	{
        bool runStepOk = runStep(false);
	
		if(!runStepOk)
			return false;
	
	} while(!finished);

	return true;
 
}

bool Scheme::runStep(bool highlight)
{

	if (finished)
	{
        QMessageBox::information(0, "Information", "This scheme was already executed.");
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

    expectedNextBlock = step_internal(expectedNextBlock, highlight);

	if (expectedNextBlock == Scheme::LoopDetected)
		return false;

	if (notExecutedBlocks.empty())
    {
		finished = true;
        QMessageBox::information(0, "Execution", "Scheme successfuly finished execution.");
    }

	return true;
}

void Scheme::removeDeletedBlocks()
{
    for (Block* block : blockScheme)
    {
        if(block->deleted)
        {
            this->removeBlock(block);
        }
    }
}

bool Scheme::preRun()
{   
    this->removeDeletedBlocks();

    if(blockScheme.size() == 0)
    {
        QMessageBox::warning(0, "No blocks", "Empty scheme cannot be executed.");
        return false;
    }

	readOnly = true;

    Block* lastBlock = searchUserDependentBlocks();

    if(lastBlock != NULL)
        lastBlock->GUIobject->unhighlight();

    notExecutedBlocks = blockScheme;

	expectedNextBlock = NULL;

	return true;
	

}

Block* Scheme::step_internal(Block* SIexpectedNextBlock, bool highlight)
{
	Block* realNextBlock = findNonDependentBlock(SIexpectedNextBlock);

	if (realNextBlock == Scheme::LoopDetected)
	{
		return Scheme::LoopDetected;
	}
	
	realNextBlock->execute();
	notExecutedBlocks.erase(std::remove(notExecutedBlocks.begin(), notExecutedBlocks.end(), realNextBlock), notExecutedBlocks.end());

    if(highlight)
        realNextBlock->GUIobject->highlight();

    if (realNextBlock->getOutputPorts().size() != 0)
	{
		if (realNextBlock->getOutputPort(0)->getConnectedPort() != NULL)
			return realNextBlock->getOutputPort(0)->getConnectedPort()->getOwnerBlock();
	}
	
	return NULL;
}

Block* Scheme::searchUserDependentBlocks()  // Returns block to store pointer to last block for .unhiglihts
{
    Block* lastBlock = NULL;
    for (Block* block : blockScheme)
	{
        int portNum = 1;
        for (vector<Port>::iterator port = block->inputPorts.begin(); port != block->inputPorts.end(); ++port)
		{
            if (port->getConnectedPort() == NULL)
			{
                for (string name : port->getNames())
				{
                    double value = port->getValue(name);
					if (value != value) //is value NaN ... value != value is true if value is NaN
					{
                        lastBlock = block;
                        block->GUIobject->highlight();

                        bool ok;
                        double value;
                        if(name == "bool")
                        {
                            QStringList items;
                            items << QString("True") << QString("False");
                            QString item = QInputDialog::getItem(0, QString("Missing value"),
                                QString("Select bool value (port #"+QString::number(portNum)+"):"), items, 0, false, &ok);

                            if(item == "True")
                                value = 0;
                            else
                                value = 1;
                        }
                        else
                        {
                            value = QInputDialog::getDouble(0, QString("Missing value"),
                                QString("Insert "+QString::fromStdString(name)+" value (port #"+QString::number(portNum)+"):"),
                                0, -2147483647, 2147483647, 5, &ok);
                        }

                        if(ok)
                            port->setValue(name, value);
                        else
                        {
                            QMessageBox::critical(0, "Error inserting value", "Execution failed. \nValue was not inserted.");
                            this->finished = true;
                            block->GUIobject->unhighlight();
                            return NULL;
                        }
					}
				}
			}
            portNum++;
		}
	}

    return lastBlock;
}


Block* Scheme::findNonDependentBlock(Block* block)
{
	loopDetectionTrace.clear();

	return findNonDependentBlock_private(block);
}




Block* Scheme::findNonDependentBlock_private(Block* block)
{

	if(std::find(loopDetectionTrace.begin(), loopDetectionTrace.end(), block) != loopDetectionTrace.end())
    {
        this->finished = true;
        QMessageBox::critical(0, "Executing error", "Loop detected.");
		return Scheme::LoopDetected;
    }
    else
		loopDetectionTrace.push_back(block);


	vector<Port> inputPorts = block->getInputPorts();

	for (vector<Port>::iterator it = inputPorts.begin(); it != inputPorts.end(); ++it)
	{

		Port* connectedPort = it->getConnectedPort();

		if (connectedPort == NULL)
		{
			continue;
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

bool Scheme::saveToFile(QString path)
{
    if(path.isEmpty())
        return false;

    QFile file(path);
    if (!file.open(QFile::WriteOnly | QFile::Text))
        return false;

    this->removeDeletedBlocks();


    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();


    stream.writeStartElement("scheme");
    stream.writeAttribute("name", QString::fromStdString(this->name));
    stream.writeAttribute("nextid", QString::number(this->nextId));

    for (Block* block : blockScheme)
    {
        stream.writeStartElement("block");
        stream.writeAttribute("type", block->GUIobject->getName());
        stream.writeAttribute("id", QString::number(block->getId()));

        stream.writeAttribute("x", QString::number(block->GUIobject->scenePos().x()));
        stream.writeAttribute("y", QString::number(block->GUIobject->scenePos().y()));

        for(int i=0; i<2; i++)  // i==0...input  i==1...output
        {
            vector<Port> portVector;

            if(i == 0)
            {
                stream.writeStartElement("input");
                portVector = block->getInputPorts();
            }
            else
            {
                stream.writeStartElement("output");
                portVector = block->getOutputPorts();
            }

            for (Port port : portVector)
            {
                stream.writeStartElement("port");

                for (string name : port.getNames())
                {
                    stream.writeStartElement("value");
                    stream.writeAttribute("name", QString::fromStdString(name));
                    stream.writeCharacters(QString::number(port.getValue(name)));
                    stream.writeEndElement(); // value
                }

                stream.writeEndElement(); // port
            }
            stream.writeEndElement(); // input/output
        }

        stream.writeEndElement(); // block
    }

    stream.writeEndElement(); // scheme
    stream.writeEndDocument();

    return true;
}

Scheme* Scheme::loadFromFile(QString path)
{

}


    /*
    QFile file(path);
    if (!file.open(QFile::ReadOnly))
        return Scheme::showError("Can't read file");

    QXmlStreamReader stream(file.readAll());

    if(!stream.readNextStartElement() || stream.name() != QLatin1String("scheme"))
        return Scheme::showError("Scheme node not found");


    int fsm = 0;
    stream.readNextStartElement();

    // --- Reading XML ---
    while(!stream.atEnd() &&  !stream.hasError())
    {
        if(fsm == -1)
            break;

        qDebug("FSM=%d",fsm);

        switch(fsm)
        {
            case 0: // -- <block> node --

                if(stream.name() != QLatin1String("block"))
                    return Scheme::showError("Block node not found");

                if(!stream.attributes().hasAttribute(QString("type")))
                    return Scheme::showError("Block type attribute not found");


                qDebug("Block"+stream.attributes().value("type").toLatin1());

                stream.readNextStartElement();
                fsm = 1;

                break;

            case 1: // --- input ---
                if(stream.name() != QLatin1String("input"))
                    return Scheme::showError("Input node not found");

                stream.readNextStartElement();
                fsm = 2;

                break;

           case 2: // input.port
                if(stream.name() != QLatin1String("port"))
                    return Scheme::showError("Input.Port node not found");

                stream.readNextStartElement();
                fsm = 3;

                break;

            case 3: // input.value
                qDebug() << stream.name();

                if(stream.name() != QLatin1String("value"))
                    return Scheme::showError("Input.Value node not found");

                if(!stream.attributes().hasAttribute(QString("name")))
                    return Scheme::showError("Input.Name attribute not found");

                qDebug(stream.attributes().value("name").toLatin1());
                qDebug(stream.text().toLatin1());  //.toDouble


                stream.readNextStartElement();  // skip </value>
                stream.readNextStartElement();

                if(stream.name() == QLatin1String("port"))
                {
                    stream.readNextStartElement();  // skip </port>
                    fsm = 2;
                }
                else if(stream.name() == QLatin1String("value"))
                    fsm = 3;
                else if(stream.name() == QLatin1String("output"))
                    fsm = 4;
                else
                {
                    qDebug("Unexpected node after Input.Value");
                    fsm = -1;

                }
        }

        */

        /*
        // -- <block> node --
        stream.readNextStartElement();

        if(stream.name() != QLatin1String("block"))
            return Scheme::showError("Block node not found");

        if(!stream.attributes().hasAttribute(QString("type")))
            return Scheme::showError("Block type attribute not found");


        qDebug("Block"+stream.attributes().value("type").toLatin1());


        // -- <input> node --
        stream.readNextStartElement();
        if(stream.name() != QLatin1String("input"))
            return Scheme::showError("Input node not found");


        stream.readNextStartElement();



        stream.readNextStartElement();
        for(int portNum = 0; stream.name() == QLatin1String("port"); portNum++)
        {

            if(stream.name() != QLatin1String("port"))
                return Scheme::showError("Port node not found");

            qDebug("Port #%d",portNum);

            stream.readNextStartElement();
            qDebug("Processig1 "+stream.name().toLatin1());
            do
            {
                if(stream.name() != QLatin1String("value"))
                    return Scheme::showError("Value node not found");

                if(!stream.attributes().hasAttribute(QString("name")))
                    return Scheme::showError("Name attribute not found");

                qDebug(stream.attributes().value("name").toLatin1());
                qDebug(stream.text().toLatin1());  //.toDouble

                stream.readNextStartElement();  ////////////////////////////////// Tu je problem do pizdy
                stream.readNextStartElement();
                qDebug("Processig2 "+stream.name().toLatin1());
            }
            while(stream.name() == QLatin1String("value"));

        }




        //qDebug("---------next");

    }

    return NULL; // @todo TEMP
}
*/

bool Scheme::showError(string msg)
{
    qDebug() << QString::fromStdString(msg);
    return false;
}
