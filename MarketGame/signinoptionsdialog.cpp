#include "signinoptionsdialog.h"
#include "ui_signinoptionsdialog.h"

SignInOptionsDialog::SignInOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignInOptionsDialog)
{
    ui->setupUi(this);
}

SignInOptionsDialog::~SignInOptionsDialog(){
    delete ui;
}

void SignInOptionsDialog::on_makeNewSimButton_clicked(){
    emit this->makeNewSimulationRequested();
}

void SignInOptionsDialog::on_termsOfServiceButton_clicked(){
    emit this->showTermsOfServicePageRequested();
}

void SignInOptionsDialog::on_aboutButton_clicked(){
    emit this->showAboutPageRequested();
}

void SignInOptionsDialog::on_loadPreviousSimButton_clicked(){
    emit this->loadNewSimulationRequested();
}
