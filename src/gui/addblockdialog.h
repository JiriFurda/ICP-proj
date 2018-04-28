#ifndef ADDBLOCKDIALOG_H
#define ADDBLOCKDIALOG_H

#include <QDialog>

#include <QTreeWidgetItem>

namespace Ui {
class AddBlockDialog;
}

class AddBlockDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBlockDialog(QWidget *parent = 0);
    ~AddBlockDialog();

private:
    Ui::AddBlockDialog *ui;

    QTreeWidget *tree;

    void fillTree();
    QTreeWidgetItem* addTreeGroup(QString name, QString decsription);
    void addTreeItem(QString name, QString decsription, QTreeWidgetItem *parent);
};

#endif // ADDBLOCKDIALOG_H
