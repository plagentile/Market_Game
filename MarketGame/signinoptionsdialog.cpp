#include "signinoptionsdialog.h"
#include "ui_signinoptionsdialog.h"

SignInOptionsDialog::SignInOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignInOptionsDialog)
{
    ui->setupUi(this);
}

SignInOptionsDialog::~SignInOptionsDialog()
{
    delete ui;
}
