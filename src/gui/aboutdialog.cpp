/**
 * Dialog window containing basic informations about this application.
 * @brief Source file for AboutDialog
 * @file aboutdialog.cpp
 * @author Jiri Furda (xfurda00)
 */

#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
