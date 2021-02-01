#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include "account.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(const MainWindow & window) = delete;
    MainWindow & operator = (const MainWindow & window) = delete;
    ~MainWindow();

private slots:
    void on_exitButton_clicked();
    void on_searchButton_clicked();

    void on_accountButton_clicked();

private:
    Ui::MainWindow *ui;
    QString key;
    Account account;
};
#endif // MAINWINDOW_H
