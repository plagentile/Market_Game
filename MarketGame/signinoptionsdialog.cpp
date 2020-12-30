#include "signinoptionsdialog.h"
#include "ui_signinoptionsdialog.h"

signInOptionsDialog::signInOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signInOptionsDialog)
{
    ui->setupUi(this);
}

signInOptionsDialog::~signInOptionsDialog()
{
    delete ui;
}
