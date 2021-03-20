#ifndef INITIALACCOUNTSETUP_H
#define INITIALACCOUNTSETUP_H

#include <QDialog>

namespace Ui {
class InitialAccountSetup;
}

class InitialAccountSetup : public QDialog
{
    Q_OBJECT

public:
    explicit InitialAccountSetup(QWidget *parent = nullptr);
    InitialAccountSetup() = delete;
    InitialAccountSetup(const InitialAccountSetup & assignThis)=delete;
    InitialAccountSetup & operator = (const InitialAccountSetup & assignThis) =delete;
    ~InitialAccountSetup();

public: signals:
       void loginRequested(const QString& key, const int32_t initBalance);

public slots:
    void on_loginButton_clicked();

private slots:
    void on_showInputButton_clicked();

private:
    bool keyOk() const noexcept;

private:
    Ui::InitialAccountSetup *ui;
};

#endif // INITIALACCOUNTSETUP_H
