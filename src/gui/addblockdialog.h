/**
 * Dialog window containing tree list of all available blocks.
 * @brief Header file for AddBlockDialog
 * @file addblockdialog.h
 * @author Jiri Furda (xfurda00)
 */

#ifndef ADDBLOCKDIALOG_H
#define ADDBLOCKDIALOG_H

#include <QDialog>

#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QGridLayout>
#include <QPushButton>
#include <QDialogButtonBox>

/**
 * @brief AddBlockDialog is dialog window containing tree list of all available blocks.
 * When a block is selected and user clicks on "Add" button, new block with selected
 * type is inserted into opened scheme.
 */
class AddBlockDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor of this class.
     * @param parent Pointer to parent widget with default value 0.
     */
    explicit AddBlockDialog(QWidget *parent = 0);
    ~AddBlockDialog();  /// @brief Destructor of this class.

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
