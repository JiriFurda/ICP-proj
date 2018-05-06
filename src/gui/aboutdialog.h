/**
 * Dialog window containing basic informations about this application.
 * @brief Header file for AboutDialog
 * @file aboutdialog.h
 * @author Jiri Furda (xfurda00)
 */

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class AboutDialog;
}

/**
 *  @brief AboutDialog is dialog window based on QDialog containing basic informations about this application.
 */
class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor of this class.
     * @param parent Pointer to parent widget with default value 0.
     */
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog(); /// @brief Destructor of class AboutDialog.

private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
