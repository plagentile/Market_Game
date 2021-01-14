#include "getuserapikey.h"
#include "ui_getuserapikey.h"

GetUserAPIKey::GetUserAPIKey(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetUserAPIKey)
{
    ui->setupUi(this);
    QPixmap pix(":/files/img/getAPIKeyBackground.jpg");
    ui->backgroundImageLabel->setPixmap(pix.scaled(ui->backgroundImageLabel->width(),ui->backgroundImageLabel->height(),Qt::KeepAspectRatioByExpanding));
    ui->APIKeyInput->setPlaceholderText("Enter API Key: ");


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

void GetUserAPIKey::on_loginButton_clicked(){
    this->APIKey = this->ui->APIKeyInput->text();
    if(this->keyOk()){
        this->close();
    }
}
