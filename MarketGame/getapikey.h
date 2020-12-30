#ifndef GETAPIKEY_H
#define GETAPIKEY_H

#include <QDialog>

namespace Ui {
class SignInDialog;
}

class SignInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignInDialog(QWidget *parent = nullptr);
    ~SignInDialog();

    const QString getAPIKey() const;
private slots:


    void on_loginButton_clicked();

private:
    Ui::SignInDialog *ui;
    QString APIKey;
};

#endif // GETAPIKEY_H
