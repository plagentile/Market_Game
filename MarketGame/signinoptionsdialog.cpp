#include "signinoptionsdialog.h"
#include "ui_signinoptionsdialog.h"

SignInOptionsDialog::SignInOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignInOptionsDialog),
    userSelectedOption(Options::NoOptionSelected)
{
    ui->setupUi(this);
}

SignInOptionsDialog::~SignInOptionsDialog(){
    delete ui;
}

SignInOptionsDialog::Options SignInOptionsDialog::run(){
    this->userSelectedOption = Options::NoOptionSelected;       //could run the same frame more than once
    this->setModal(true);
    this->exec();
    return this->userSelectedOption;
}

void SignInOptionsDialog::on_makeNewSimButton_clicked(){
    this->userSelectedOption = Options::NewSimulation;
    this->close();
}

void SignInOptionsDialog::on_termsOfServiceButton_clicked(){
    this->userSelectedOption = Options::TermsOfService;
    this->close();
}

void SignInOptionsDialog::on_aboutButton_clicked(){
    this->userSelectedOption = Options::About;
    this->close();
}
