/**
 * Dialog window containing informations about authors of this application.
 * @brief Header file for CreditsDialog
 * @file creditsdialog.h
 * @author Jiri Furda (xfurda00)
 */

#ifndef CREDITSDIALOG_H
#define CREDITSDIALOG_H

#include <QDialog>

namespace Ui {
class CreditsDialog;
}

/**
 *  @brief CreditsDialog is dialog window based on QDialog containing informations about authors of this application.
 */
class CreditsDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor of this class.
     * @param parent Pointer to parent widget with default value 0.
     */
    explicit CreditsDialog(QWidget *parent = 0);
    ~CreditsDialog();   /// @brief Destructor of this class.

private:
    Ui::CreditsDialog *ui;
};

#endif // CREDITSDIALOG_H
