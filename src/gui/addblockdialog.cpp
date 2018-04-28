#include "addblockdialog.h"
#include "ui_addblockdialog.h"

AddBlockDialog::AddBlockDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBlockDialog)
{
    //ui->setupUi(this);

    // --- Setup window ---
    this->setWindowTitle("Add new block - BlockEditor");
    this->setMinimumWidth(400);
    this->setLayout(new QGridLayout);

    // --- Setup tree widget ---
    tree = new QTreeWidget;
    tree->setColumnCount(2);
    tree->setHeaderLabels(QStringList() << "Name" << "Description");
    this->layout()->addWidget(tree);

    // --- Fill tree widget ---
    this->fillTree();

    // --- Buttons ---
    QPushButton *addBlockButton = new QPushButton("Add");
    addBlockButton->setDefault(true);
    //QObject::connect(addBlockButton, SIGNAL(clicked()), this, SLOT(on_addBlockButton_clicked()));
    QObject::connect(addBlockButton, SIGNAL(clicked()), this->parentWidget(), SLOT(debug())); ///////////////////////////

    QDialogButtonBox *buttonBox = new QDialogButtonBox();
    buttonBox->addButton(addBlockButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(QDialogButtonBox::Close);

    this->layout()->addWidget(buttonBox);
}

AddBlockDialog::~AddBlockDialog()
{
    // @todo Crashes when exiting
    delete ui;
}

void AddBlockDialog::fillTree()
{
    QTreeWidgetItem *arithmeticGroup = this->addTreeGroup("Arithmetic", "Basic arithmetic blocks for float numbers");
    QTreeWidgetItem *logicGroup = this->addTreeGroup("Logic", "Basic logic blocks for boolean values");

    this->addTreeItem("Add", "Adds two float numbers", arithmeticGroup);
    this->addTreeItem("Sub", "Subs two float numbers", arithmeticGroup);

    this->addTreeItem("Not", "Reverses boolean value", logicGroup);
}

QTreeWidgetItem *AddBlockDialog::addTreeGroup(QString name, QString decsription)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(tree);
    item->setText(0,name);
    item->setText(1,decsription);

    tree->addTopLevelItem(item); // @todo There is also AddTopLevelItems

    return item;
}

void AddBlockDialog::addTreeItem(QString name, QString decsription, QTreeWidgetItem *parent)
{
   QTreeWidgetItem *item = new QTreeWidgetItem();
   item->setText(0,name);
   item->setText(1,decsription);

   parent->addChild(item);

}

void AddBlockDialog::on_addBlockButton_clicked()
{
    ///////////////////////////////////////////
    //QObject::connect(this, SIGNAL(createBlockRequest()), this->parentWidget(), SLOT(createBlock(tree->selectedItems().text(0))));
    //QObject::connect(this, SIGNAL(createBlockRequest()), this->parentWidget(), SLOT(createBlock("Test")));
    //emit(createBlockRequest());
    //this->parentWidget()->createBlock("Test");
}

