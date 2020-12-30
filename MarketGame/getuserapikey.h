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
    ~GetUserAPIKey();

    const QString getAPIKey() const;
private slots:
    void on_loginButton_clicked();

private:
    Ui::GetUserAPIKey *ui;
    QString APIKey;
};

#endif // GETUSERAPIKEY_H
