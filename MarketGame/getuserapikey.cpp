#include "getuserapikey.h"
#include "ui_getuserapikey.h"


GetUserAPIKey::GetUserAPIKey(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetUserAPIKey),
    status(ApplicationStatus::Status::Unchanged)
{
    ui->setupUi(this);
}

GetUserAPIKey::~GetUserAPIKey(){
    delete ui;
}

const QString GetUserAPIKey::getAPIKey() const{
    return this->APIKey;
}

/**
 * @brief GetUserAPIKey::keyOk
 * @return
 * Can add (initial) key checks here
 */
bool GetUserAPIKey::keyOk() const{
    if(this->APIKey.size() > 5) return true;
    return false;
}

ApplicationStatus::Status GetUserAPIKey::run()
{
    while(this->status == ApplicationStatus::Status::Unchanged){
        this->setModal(true);
        this->exec();
    }
    return this->status;
}


void GetUserAPIKey::on_loginButton_clicked(){
    this->APIKey = this->ui->APIKeyInput->text();
    if(this->keyOk()){
         this->status = ApplicationStatus::Status::ExitSuccessfully;
        this->close();
    }
}

void GetUserAPIKey::closeEvent(QCloseEvent *event){
    if(this->status == ApplicationStatus::Status::Unchanged)
        status = ApplicationStatus::Status::UserClosedApplication;
    event->accept();
}

void GetUserAPIKey::on_showInputButton_clicked()
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
