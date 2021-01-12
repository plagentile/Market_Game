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
    ~SignInOptionsDialog();

private:
    Ui::SignInOptionsDialog *ui;
};

#endif // SIGNINOPTIONSDIALOG_H
