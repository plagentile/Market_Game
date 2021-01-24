#include "signinoptionsdialog.h"
#include "ui_signinoptionsdialog.h"

SignInOptionsDialog::SignInOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignInOptionsDialog),
    userSelectedOption(Options::NoOptionSelected)
{
    ui->setupUi(this);
    QPixmap pix(":/files/img/welcomeScreenBackground.jpg");
    ui->backgroundImageLabel->setPixmap(pix.scaled(ui->backgroundImageLabel->width(),ui->backgroundImageLabel->height(),Qt::KeepAspectRatioByExpanding));

}

SignInOptionsDialog::~SignInOptionsDialog()
{
    delete ui;
}

SignInOptionsDialog::Options SignInOptionsDialog::run()
{
    this->setModal(true);
    this->exec();
    return this->userSelectedOption;
}

void SignInOptionsDialog::on_makeNewSimButton_clicked(){
    this->userSelectedOption = Options::NewSimulation;
    this->close();
}
