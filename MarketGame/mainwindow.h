#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include "getuserapikey.h"
#include "signinoptionsdialog.h"

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

private:
     void GetSignIn();
     bool keyOk();

private:
    Ui::MainWindow *ui;
    GetUserAPIKey *pGetUserAPIKey;
    QString key;
};
#endif // MAINWINDOW_H
