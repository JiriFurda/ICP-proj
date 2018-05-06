/**
 * Dialog window containing informations about authors of this application.
 * @brief Source file for CreditsDialog
 * @file creditsdialog.cpp
 * @author Jiri Furda (xfurda00)
 */

#include "creditsdialog.h"
#include "ui_creditsdialog.h"

CreditsDialog::CreditsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditsDialog)
{
    ui->setupUi(this);
}

CreditsDialog::~CreditsDialog()
{
    delete ui;
}
