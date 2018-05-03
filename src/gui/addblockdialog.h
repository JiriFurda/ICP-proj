#ifndef ADDBLOCKDIALOG_H
#define ADDBLOCKDIALOG_H

#include <QDialog>

#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QGridLayout>
#include <QPushButton>
#include <QDialogButtonBox>

class AddBlockDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBlockDialog(QWidget *parent = 0);
    ~AddBlockDialog();

private:

    QTreeWidget *tree;

    void fillTree();
    QTreeWidgetItem* addTreeGroup(QString name, QString decsription);
    void addTreeItem(QString name, QString decsription, QTreeWidgetItem *parent);

private slots:
    void on_addBlockButton_triggered();
    void on_closeButton_triggered();

signals:
    void addBlock_request(QString);
};

#endif // ADDBLOCKDIALOG_H
