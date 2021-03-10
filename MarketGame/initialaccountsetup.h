#ifndef INITIALACCOUNTSETUP_H
#define INITIALACCOUNTSETUP_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class InitialAccountSetup;
}

class InitialAccountSetup : public QDialog
{
    Q_OBJECT

public:
    explicit InitialAccountSetup(QWidget *parent = nullptr);
    InitialAccountSetup(const InitialAccountSetup & assignThis)=delete;
    InitialAccountSetup & operator = (const InitialAccountSetup & assignThis) =delete;
    ~InitialAccountSetup();

    enum class Status
    {
        Unchanged,
        ExitSuccessfully,
        UserClosedApplication,
        IncorrectAPIKey
    };

    const QString getAPIKey() const noexcept;
    double getInitBalance() const noexcept;
    bool keyOk() const noexcept;
    Status run();

private slots:
    void on_loginButton_clicked() noexcept;
    void on_showInputButton_clicked();

private:
    double initBalance;
    Ui::InitialAccountSetup *ui;
    QString APIKey;
    Status status;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // INITIALACCOUNTSETUP_H
