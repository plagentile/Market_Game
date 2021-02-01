#include "termsofservice.h"
#include "ui_termsofservice.h"

TermsOfService::TermsOfService(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TermsOfService)
{
    ui->setupUi(this);
}

TermsOfService::~TermsOfService()
{
    delete ui;
}
