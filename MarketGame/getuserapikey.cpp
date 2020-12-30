#include "getuserapikey.h"
#include "ui_getuserapikey.h"

GetUserAPIKey::GetUserAPIKey(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetUserAPIKey)
{
    ui->setupUi(this);
}

GetUserAPIKey::~GetUserAPIKey(){
    delete ui;
}

const QString GetUserAPIKey::getAPIKey() const{
    return this->APIKey;
}

void GetUserAPIKey::on_loginButton_clicked(){
    this->APIKey = this->ui->APIKeyInput->text();
}
