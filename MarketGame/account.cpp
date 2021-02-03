#include "account.h"
#include "ui_account.h"


Account::Account(QWidget *parent, const double balance, const QString APIKey):
     QDialog(parent),
     accountBalance(balance),
     availableFunds(balance),
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

double Account::getAvailableFunds() const{
    return this->availableFunds;
}

void Account::run(){
    ui->availableFundsSpinBox->setValue(availableFunds);
    ui->APIKeyLineEdit->setText(APIKey);
    this->enableDisableButton();
    this->exec();
}

void Account::enableDisableButton()
{
    //first page
    if(this->ui->accountOverviewStackedWidget->currentIndex() == 0){
        this->ui->nextButton->setEnabled(true);
        this->ui->backButton->setEnabled(false);
        return;
    }
    //last page
    if(this->ui->accountOverviewStackedWidget->currentIndex() == this->ui->accountOverviewStackedWidget->count() -1){
        this->ui->nextButton->setEnabled(false);
        this->ui->backButton->setEnabled(true);
        return;
    }
    //middle
    this->ui->backButton->setEnabled(true);
    this->ui->nextButton->setEnabled(true);
}

void Account::on_changeAPIKeyButton_clicked(){
    if(this->ui->APIKeyLineEdit->isReadOnly()){
        this->ui->APIKeyLineEdit->setReadOnly(false);
        this->ui->changeAPIKeyButton->setText("Save");
        this->ui->changeAPIKeyButton->setFocus();
        return;
    }
    else{
        this->ui->changeAPIKeyButton->setText("Change");
        this->APIKey = this->ui->APIKeyLineEdit->text();
        this->ui->APIKeyLineEdit->setReadOnly(true);
    }
}

void Account::on_changeAvailableFundsButton_clicked(){
    if(this->ui->availableFundsSpinBox->isReadOnly()){
        this->ui->availableFundsSpinBox->setReadOnly(false);
        this->ui->changeAvailableFundsButton->setText("Save");
        this->ui->availableFundsSpinBox->setFocus();
        return;
    }
    else{
        this->ui->changeAvailableFundsButton->setText("Change");
        this->availableFunds = this->ui->availableFundsSpinBox->value();
        this->ui->availableFundsSpinBox->setReadOnly(true);
    }
}

void Account::on_nextButton_clicked(){
    int index = this->ui->accountOverviewStackedWidget->currentIndex();
    index++;

    if(index >= this->ui->accountOverviewStackedWidget->count()){
       index = this->ui->accountOverviewStackedWidget->count();
       index--;
    }
    this->ui->accountOverviewStackedWidget->setCurrentIndex(index);
    this->enableDisableButton();
}

void Account::on_cancelButton_clicked(){
    this->close();
}

void Account::on_backButton_clicked(){
    int index = this->ui->accountOverviewStackedWidget->currentIndex();
    index--;
    if(index <= 0){
       index = 0;
    }
    this->ui->accountOverviewStackedWidget->setCurrentIndex(index);
    this->enableDisableButton();
}
