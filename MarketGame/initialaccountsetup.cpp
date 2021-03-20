#include "initialaccountsetup.h"
#include "ui_initialaccountsetup.h"

InitialAccountSetup::InitialAccountSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitialAccountSetup)
{
    ui->setupUi(this);
}

InitialAccountSetup::~InitialAccountSetup(){
    delete ui;
}


/**
 * @brief GetUserAPIKey::keyOk
 * @return
 * Can add (initial) key checks here
 */
bool InitialAccountSetup::keyOk() const noexcept{
    if(this->ui->APIKeyInput->text() > 5) return true;
    return false;
}

void InitialAccountSetup::on_loginButton_clicked(){
    if(this->keyOk()){
        emit this-> loginRequested(this->ui->APIKeyInput->text(), this->ui->accountBalanceInput->value());
    }
}

void InitialAccountSetup::on_showInputButton_clicked(){
    if(this->ui->APIKeyInput->echoMode() == QLineEdit::Normal){
        this->ui->APIKeyInput->setEchoMode(QLineEdit::Password);
        this->ui->showInputButton->setStyleSheet("border-image: url(:/files/img/hideInput.png) 0 0 0 0 stretch stretch;");
    }
    else{
        this->ui->APIKeyInput->setEchoMode(QLineEdit::Normal);
        this->ui->showInputButton->setStyleSheet("border-image: url(:/files/img/showInput.png) 0 0 0 0 stretch stretch;");
    }
}

