#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QRegExpValidator>
#include <QRegExp>
#include <QStandardItemModel>
#include "account.h"
#include "symbolternarysearchtree.h"
#include "requestencapsulator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, const int32_t initBalance = 0, const QString initAPIKey = "", const SymbolTernarySearchTree *pTST = nullptr );
    MainWindow() = delete;
    MainWindow(const MainWindow & window) = delete;
    MainWindow & operator = (const MainWindow & window) = delete;
    ~MainWindow();

    enum class Status
    {
        Normal,
        NewSimulation,
        LoadSimulation,
        ExitNormal,
        ExitError
    };

    Status getStatus() const;

private:
    void refreshSymbolInformation();
    void showViewSymbolPage();

private slots:
    void on_symbolSearchLineEdit_textChanged(const QString &arg1);
    void on_symbolListResults_clicked(const QModelIndex &index);
    void on_symbolSearchLineEdit_returnPressed();
    void on_searchSymbolButton_clicked();

private:
    RequestEncapsulator requestEncapsulator;
    QStandardItemModel model;
    Ui::MainWindow *ui;
    Account * pAccount;
    const SymbolTernarySearchTree * pSymbolTST;
    QVector<const SymbolTernarySearchTree::Node *> vSearchResults;
    Status status;
};
#endif // MAINWINDOW_H
