#ifndef GETUSERAPIKEY_H
#define GETUSERAPIKEY_H

#include <QDialog>
#include <QCloseEvent>
#include "applicationstatus.h"

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
    ApplicationStatus::Status run();

private slots:
    void on_loginButton_clicked();

    void on_showInputButton_clicked();

private:
    Ui::GetUserAPIKey *ui;
    QString APIKey;
    ApplicationStatus::Status status;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // GETUSERAPIKEY_H
