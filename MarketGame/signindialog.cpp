#include "signindialog.h"
#include "ui_signindialog.h"

SignInDialog::SignInDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::SignInDialog), APIKey("")
{
    ui->setupUi(this);
    setWindowTitle("Login");
    ui->APIKeyInput->setPlaceholderText("Enter API Key");
    ui->APIKeyInput->setEchoMode(QLineEdit::Password);

}

SignInDialog::~SignInDialog()
{
    delete ui;
}

const QString SignInDialog::getAPIKey() const{
    return this->APIKey;
}

void SignInDialog::on_loginButton_clicked(){
    this->APIKey = this->ui->APIKeyInput->text();
    printf("Key: %ls\n", qUtf16Printable(this->APIKey) );

}
