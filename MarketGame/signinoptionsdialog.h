#ifndef SIGNINOPTIONSDIALOG_H
#define SIGNINOPTIONSDIALOG_H
#include <QDialog>

namespace Ui {
class SignInOptionsDialog;
}

class SignInOptionsDialog : public QDialog
{
    Q_OBJECT

public:
    enum class Options
    {
       NoOptionSelected,
       TermsOfService,
       About,
       NewSimulation,
       LoadPreviousSave
    };

public:
    explicit SignInOptionsDialog(QWidget *parent = nullptr);
    SignInOptionsDialog(const SignInOptionsDialog & assignThis) = delete;
    SignInOptionsDialog & operator =(const SignInOptionsDialog & assignThis) = delete;
   ~SignInOptionsDialog();

    Options run();

private slots:
    void on_makeNewSimButton_clicked();
    void on_termsOfServiceButton_clicked();

private:
    Ui::SignInOptionsDialog *ui;
    Options userSelectedOption;
};

#endif // SIGNINOPTIONSDIALOG_H
