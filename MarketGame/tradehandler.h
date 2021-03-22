#ifndef TRADEHANDLER_H
#define TRADEHANDLER_H

#include <QDialog>

namespace Ui {
class TradeHandler;
}

class TradeHandler : public QDialog
{
    Q_OBJECT

public:
    explicit TradeHandler(QWidget *parent = nullptr);
    ~TradeHandler();

private:
    Ui::TradeHandler *ui;
};

#endif // TRADEHANDLER_H
