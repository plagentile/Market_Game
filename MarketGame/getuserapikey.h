#ifndef GETUSERAPIKEY_H
#define GETUSERAPIKEY_H

#include <QDialog>

namespace Ui {
class GetUserAPIKey;
}

class GetUserAPIKey : public QDialog
{
    Q_OBJECT

public:
    explicit GetUserAPIKey(QWidget *parent = nullptr);

    GetUserAPIKey(const GetUserAPIKey & assignThis) =delete;
    GetUserAPIKey & operator = (const GetUserAPIKey & assignThis) =delete;
    ~GetUserAPIKey();

    const QString getAPIKey() const;
    bool keyOk() const;

private slots:
    void on_loginButton_clicked();

private:
    Ui::GetUserAPIKey *ui;
    QString APIKey;
};

#endif // GETUSERAPIKEY_H
