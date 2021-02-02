#include "account.h"
#include "ui_account.h"


Account::Account(QWidget *parent, const double balance, const QString APIKey):
     QDialog(parent),
     accountBalance(balance),
     ui(new Ui::Account),
     APIKey(APIKey)
{
    ui->setupUi(this);
}

Account::~Account(){
    delete ui;
}

const QString Account::getAPIKey() const{
    return this->APIKey;
}

double Account::getAccountBalance() const{
    return this->accountBalance;
}

void Account::run(){
    ui->balanceSpinBox->setValue(accountBalance);
    ui->APIKeyLineEdit->setText(APIKey);
    this->exec();
}

void Account::on_changeAPIKeyButton_clicked(){

    if(this->ui->APIKeyLineEdit->isReadOnly()){
        this->ui->APIKeyLineEdit->setReadOnly(false);
        this->ui->changeAPIKeyButton->setText("Save");
        return;
    }
    else{
        this->ui->changeAPIKeyButton->setText("Change");
        this->APIKey = this->ui->APIKeyLineEdit->text();
        this->ui->APIKeyLineEdit->setReadOnly(true);
    }
}

void Account::on_changeBalanceButton_clicked()
{
    if(this->ui->balanceSpinBox->isReadOnly()){
        this->ui->balanceSpinBox->setReadOnly(false);
        this->ui->changeBalanceButton->setText("Save");
        this->ui->balanceSpinBox->setFocus();
        return;
    }
    else{
        this->ui->changeBalanceButton->setText("Change");
        this->accountBalance = this->ui->balanceSpinBox->value();
        this->ui->balanceSpinBox->setReadOnly(true);
    }
}
