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
    explicit SignInOptionsDialog(QWidget *parent = nullptr);
    SignInOptionsDialog() =delete;
    SignInOptionsDialog(const SignInOptionsDialog & assignThis) = delete;
    SignInOptionsDialog & operator =(const SignInOptionsDialog & assignThis) = delete;
   ~SignInOptionsDialog();

public:signals:
     void makeNewSimulationRequested();
     void loadNewSimulationRequested();
     void showAboutPageRequested();
     void showTermsOfServicePageRequested();

private slots:
    void on_makeNewSimButton_clicked();
    void on_termsOfServiceButton_clicked();
    void on_aboutButton_clicked();

    void on_loadPreviousSimButton_clicked();

private:
    Ui::SignInOptionsDialog *ui;
};

#endif // SIGNINOPTIONSDIALOG_H
