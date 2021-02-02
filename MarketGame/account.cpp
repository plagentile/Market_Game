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

void Account::run()
{
    ui->balanceLabel->setText(QString::number(this->accountBalance, 'f', 3));
    ui->APIKeyLabel->setText(APIKey);
    this->exec();
}
