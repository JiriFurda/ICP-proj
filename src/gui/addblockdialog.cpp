#include "addblockdialog.h"

AddBlockDialog::AddBlockDialog(QWidget *parent) : QDialog(parent)
{
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
    QObject::connect(addBlockButton, SIGNAL(clicked()), this, SLOT(on_addBlockButton_triggered()));

    QPushButton *closeButton = new QPushButton("Close");
    QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(on_closeButton_triggered()));

    QDialogButtonBox *buttonBox = new QDialogButtonBox();
    buttonBox->addButton(addBlockButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(closeButton, QDialogButtonBox::ActionRole);    // Could use StandartButton Close but I don't know how to implement it

    this->layout()->addWidget(buttonBox);
}

AddBlockDialog::~AddBlockDialog()
{
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
    item->setExpanded(true);

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

void AddBlockDialog::on_addBlockButton_triggered()
{
    QObject::connect(this, SIGNAL(addBlock_request(QString)), this->parentWidget(), SLOT(createBlock(QString)));    // Connect signal to MainWindow's slot

    QTreeWidgetItem *selectedItem = tree->currentItem();

    if(selectedItem->childCount() != 0)   // Check if group selected instead of block
    {
        QMessageBox::warning(this, tr("Add block error"), tr("Invalid block selected.") );
        return;
    }

    emit(addBlock_request(selectedItem->text(0)));   // @warning currenItem is set to first one when no item is selected

    this->close();  // Close this window
}

void AddBlockDialog::on_closeButton_triggered()
{
    this->close();
}
