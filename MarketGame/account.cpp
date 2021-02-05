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
    this->enableDisableButton();
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
    this->exec();
    this->enableDisableButton();
}

void Account::enableDisableButton()
{
    //first page
    if(this->ui->accountOverviewStackedWidget->currentIndex() == 0){
        this->ui->viewAccountPositionsButton->setEnabled(true);
        this->ui->viewAccountPositionsButton->show();

        this->ui->viewAccountSnapshotButton->setEnabled(false);
        this->ui->viewAccountSnapshotButton->hide();
    }
    else{
      //second page, there are no other pages
      this->ui->viewAccountPositionsButton->setEnabled(false);
      this->ui->viewAccountPositionsButton->hide();

      this->ui->viewAccountSnapshotButton->setEnabled(true);
      this->ui->viewAccountSnapshotButton->show();
    }
    this->ui->changeAPIKeyButton->setText("Change");
    this->ui->APIKeyLineEdit->setReadOnly(true);

    this->ui->changeAvailableFundsButton->setText("Change");
    this->ui->availableFundsSpinBox->setReadOnly(true);

    return;
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

void Account::on_viewAccountPositionsButton_clicked(){
    this->ui->accountOverviewStackedWidget->setCurrentIndex(1);
    this->enableDisableButton();
}

void Account::on_cancelButton_clicked(){
    this->close();
}

void Account::on_viewAccountSnapshotButton_clicked(){
    this->ui->accountOverviewStackedWidget->setCurrentIndex(0);
    this->enableDisableButton();
}
