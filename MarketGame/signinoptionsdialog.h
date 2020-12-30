#ifndef SIGNINOPTIONSDIALOG_H
#define SIGNINOPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class signInOptionsDialog;
}

class signInOptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit signInOptionsDialog(QWidget *parent = nullptr);
    ~signInOptionsDialog();

private:
    Ui::signInOptionsDialog *ui;
};

#endif // SIGNINOPTIONSDIALOG_H
