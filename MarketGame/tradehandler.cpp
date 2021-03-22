#include "tradehandler.h"
#include "ui_tradehandler.h"

TradeHandler::TradeHandler(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TradeHandler)
{
    ui->setupUi(this);
}

TradeHandler::~TradeHandler()
{
    delete ui;
}
