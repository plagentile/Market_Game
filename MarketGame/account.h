#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QDialog>

namespace Ui {
class Account;
}

class Account : public QDialog
{
    Q_OBJECT

public:
    explicit Account(QWidget *parent = nullptr, const double balance =0.0, const QString APIKey = "");
    Account() = delete;
    Account(const Account & assignThis) =delete;
    Account & operator = (const Account & assignThis) = delete;
    ~Account();

    const QString getAPIKey() const;
    double getAccountBalance() const;

    void run();
private slots:
    void on_changeAPIKeyButton_clicked();
    void on_changeBalanceButton_clicked();

private:
    double accountBalance;
    Ui::Account *ui;
    QString APIKey;
};

#endif // ACCOUNT_H
