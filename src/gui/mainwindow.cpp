/**
 * Main window of the application.
 * @brief Source file for MainWindow
 * @file mainwindow.c
 * @author Jiri Furda (xfurda00)
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Unnamed scheme - BlockEditor");
    this->showMaximized();

    // === Scheme view ===
    this->view = new QGraphicsView(this);
    this->view->setRenderHint(QPainter::Antialiasing);
    this->centralWidget()->layout()->addWidget(view);

    this->scene = new SchemeScene();
    this->view->setScene(this->scene);

    // --- Backend ---
    this->backendScheme = new Scheme("Unnamed scheme");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_BlockEditor_triggered()
{
    AboutDialog dialog;
    dialog.setModal(true);  // Can't click on other window
    dialog.exec();
}

void MainWindow::on_actionCredits_triggered()
{
    CreditsDialog dialog;
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::on_actionAdd_triggered()
{
    AddBlockDialog dialog(this);
    dialog.setModal(true);
    dialog.exec();
}

Block* MainWindow::createBlock(QString name)
{
    Block *block;

    if(name == "Add")
        block = new BlockAdd();
    else if(name == "Sub")
        block = new BlockSub();
    else if(name == "Mul")
        block = new BlockMul();
    else if(name == "Div")
        block = new BlockDiv();
    else if(name == "CxAdd")
        block = new BlockCxAdd();
    else if(name == "CxSub")
        block = new BlockCxSub();
    else if(name == "CxMul")
        block = new BlockCxMul();
    else if(name == "CxDiv")
        block = new BlockCxDiv();
    //else if(name == "Not")
    //    block = new BlockNot();
    else if(name == "And")
        block = new BlockAnd();
    else if(name == "Or")
        block = new BlockOr();
    else if(name == "Xor")
        block = new BlockXor();
    else
    {
        QMessageBox::critical(this, "Error creating block", "Unexpect name received when creating block");
        return NULL;
    }

    new BlockGraphicItem(this->scene, name, block);
    this->backendScheme->addBlock(block);   // @todo Temporary, should be in SchemeScene
    this->backendScheme->setFinished(false);

    return block;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, "Quit application", "Do you really want to quit this application?", QMessageBox::Yes | QMessageBox::No))
    {
        event->accept();
    }
}

void MainWindow::on_actionSave_File_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save scheme to file"), "",
        tr("Block scheme (*.scheme);;All Files (*)"));

    bool ok = this->backendScheme->saveToFile(fileName);

    if(ok)
    {
        QMessageBox::information(
            this,
            tr("Scheme saved"),
            tr("Scheme was successfuly saved to file."));
    }
    else
    {
        QMessageBox::critical(
            this,
            tr("Saving error"),
            tr("There was an error saving scheme to file."));
    }
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open scheme from file"), "",
        tr("Block scheme (*.scheme);;All Files (*)"));

    SchemeScene* oldFrontendScheme = this->scene;
    Scheme* oldBackendScheme = this->backendScheme;

    this->scene = new SchemeScene();
    this->backendScheme = new Scheme("Test");





    if(this->loadFromFile(fileName))
    {
        this->view->setScene(this->scene);
    }
    else
    {
        this->scene = oldFrontendScheme;
        this->backendScheme = oldBackendScheme;
    }

    /*
    QMessageBox::information(
        this,
        tr("Not implemeted"),
        tr("Opening scheme from file is not yet implemented.") );*/
}

bool MainWindow::loadFromFile(QString path)
{
    // --- Check path ---
    if(path.isEmpty())
        return this->showOpeningError("Empty file path");

    // --- Load XML ---
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path.toLatin1());


    // --- <scheme> node ---
    tinyxml2::XMLElement *schemeNode = doc.FirstChildElement("scheme");

    if(schemeNode == nullptr)
        return this->showOpeningError("Scheme node not found");

    int nextId;
    schemeNode->QueryIntAttribute("nextid", &nextId);
    this->backendScheme->setNextId(nextId);

    bool finished;
    schemeNode->QueryBoolAttribute("finished", &finished);
    this->backendScheme->setFinished(finished);


    // --- <block> nodes ---
    for (tinyxml2::XMLElement* blockNode = schemeNode->FirstChildElement("block"); blockNode != NULL; blockNode = blockNode->NextSiblingElement("block"))
    {
        Block* newBlock = this->createBlock(blockNode->Attribute("type"));
        newBlock->GUIobject->setPos(QString(blockNode->Attribute("x")).toDouble(),QString(blockNode->Attribute("y")).toDouble());
    }


    // --- <port> and <value> nodes ---
    for(tinyxml2::XMLElement* blockNode = schemeNode->FirstChildElement("block"); blockNode != NULL; blockNode = blockNode->NextSiblingElement("block"))
    {
        int portNum = 0;


        // -- <input> --
        tinyxml2::XMLElement *inputNode = blockNode->FirstChildElement("input");
        if(inputNode == nullptr)
            return this->showOpeningError("Input node not found");

        for(tinyxml2::XMLElement* portNode = inputNode->FirstChildElement("port"); portNode != NULL; portNode = portNode->NextSiblingElement("port"))
        {
            int id;
            blockNode->QueryIntAttribute("id", &id);
            Block *block = this->backendScheme->getBlockById(id);

            if(block == NULL)
                return this->showOpeningError("Block search by id was not successful");

            if(portNode->Attribute("connectedblock") != NULL)
            {
                int connectedBlockId;
                portNode->QueryIntAttribute("connectedblock", &connectedBlockId);

                Port* port = block->getInputPort(portNum);
                Block* otherBlock = this->backendScheme->getBlockById(connectedBlockId);
                Port* otherPort = otherBlock->getOutputPort(0); // Port to connect to

                new ConnectionLineItem(this->scene, block->GUIobject, otherBlock->GUIobject, port, otherPort);
            }

            for (tinyxml2::XMLElement* valueNode = portNode->FirstChildElement("value"); valueNode != NULL; valueNode = valueNode->NextSiblingElement("value"))
            {
                //if(name == NULL)    @todo
                //    return this->showOpeningError("Name param not found")

                double value;
                valueNode->QueryDoubleText(&value);

                block->getInputPort(portNum)->setValue(valueNode->Attribute("name"), value);
            }

            portNum++;
        }


        // -- <output> --
        tinyxml2::XMLElement *outputNode = blockNode->FirstChildElement("output");
        if(inputNode == nullptr)
            return this->showOpeningError("Output node not found");

        for(tinyxml2::XMLElement* portNode = outputNode->FirstChildElement("port"); portNode != NULL; portNode = portNode->NextSiblingElement("port"))
        {
            int id;
            blockNode->QueryIntAttribute("id", &id);
            Block *block = this->backendScheme->getBlockById(id);

            if(block == NULL)
                return this->showOpeningError("Block search by id was not successful");

            for (tinyxml2::XMLElement* valueNode = portNode->FirstChildElement("value"); valueNode != NULL; valueNode = valueNode->NextSiblingElement("value"))
            {
                //if(name == NULL)    @todo
                //    return this->showOpeningError("Name param not found")

                double value;
                valueNode->QueryDoubleText(&value);

                block->getOutputPort(0)->setValue(valueNode->Attribute("name"), value);
            }
        }
    }

    return true;
}

bool MainWindow::showOpeningError(string msg)
{
    QMessageBox::critical(
        this,
        tr("Opening error"),
        QString::fromStdString(msg));
    return false;
}

void MainWindow::on_actionNew_File_triggered()
{
    scene->clear();
    delete this->backendScheme;
    this->backendScheme = new Scheme("Unnamed scheme");
    this->setWindowTitle("Unnamed scheme - BlockEditor");
}

void MainWindow::on_actionRun_triggered()
{
    this->backendScheme->run();
}

void MainWindow::on_actionStep_triggered()
{
    this->backendScheme->runStep(true);
}

void MainWindow::on_actionExit_connection_mode_triggered()
{
    this->scene->exitConnectingBlocks();
}

void MainWindow::on_actionRename_file_triggered()
{
    bool ok;
        QString text = QInputDialog::getText(this, tr("Rename scheme"),
                                             tr("New name:"), QLineEdit::Normal,
                                             "", &ok);
        if (ok && !text.isEmpty())
            this->setWindowTitle(text+" - BlockEditor");
}

void MainWindow::on_actionRevert_triggered()
{
    if (QMessageBox::Yes == QMessageBox::question(this, "Revert scheme", "Do you really want to revert this to pre-execute state?", QMessageBox::Yes | QMessageBox::No))
    {
        this->backendScheme->revert();
    }
}
