#include "getuserapikey.h"
#include "ui_getuserapikey.h"

GetUserAPIKey::GetUserAPIKey(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetUserAPIKey)
{
    ui->setupUi(this);
    QPixmap pix(":/resources/img/aPic.jpg");
    int w = ui->picLabel->width();
    int h = ui->picLabel->height();
    ui->picLabel->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));


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
