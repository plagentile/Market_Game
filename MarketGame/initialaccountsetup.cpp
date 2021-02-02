#include "initialaccountsetup.h"
#include "ui_initialaccountsetup.h"

InitialAccountSetup::InitialAccountSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitialAccountSetup),
    status(ApplicationStatus::Status::Unchanged)
{
    ui->setupUi(this);
}

InitialAccountSetup::~InitialAccountSetup(){
    delete ui;
}

const QString InitialAccountSetup::getAPIKey() const{
    return this->APIKey;
}

double InitialAccountSetup::getInitBalance() const
{
    return this->initBalance;
}

/**
 * @brief GetUserAPIKey::keyOk
 * @return
 * Can add (initial) key checks here
 */
bool InitialAccountSetup::keyOk() const{
    if(this->APIKey.size() > 5) return true;
    return false;
}

ApplicationStatus::Status InitialAccountSetup::run()
{
    while(this->status == ApplicationStatus::Status::Unchanged){
        this->setModal(true);
        this->exec();
    }
    return this->status;
}


void InitialAccountSetup::on_loginButton_clicked(){
    this->initBalance = this->ui->accountBalanceInput->value();
    this->APIKey = this->ui->APIKeyInput->text();
    if(this->keyOk()){
         this->status = ApplicationStatus::Status::ExitSuccessfully;
        this->close();
    }
}

void InitialAccountSetup::closeEvent(QCloseEvent *event){
    if(this->status == ApplicationStatus::Status::Unchanged)
        status = ApplicationStatus::Status::UserClosedApplication;
    event->accept();
}

void InitialAccountSetup::on_showInputButton_clicked()
{
    if(this->ui->APIKeyInput->echoMode() == QLineEdit::Normal){
        this->ui->APIKeyInput->setEchoMode(QLineEdit::Password);
        this->ui->showInputButton->setStyleSheet("border-image: url(:/files/img/hideInput.png) 0 0 0 0 stretch stretch;");
    }
    else{
        this->ui->APIKeyInput->setEchoMode(QLineEdit::Normal);
        this->ui->showInputButton->setStyleSheet("border-image: url(:/files/img/showInput.png) 0 0 0 0 stretch stretch;");
    }
}

