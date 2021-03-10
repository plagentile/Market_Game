#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QRegExpValidator>
#include <QRegExp>
#include <QStandardItemModel>
#include "account.h"
#include "initialaccountsetup.h"
#include "symbolternarysearchtree.h"
#include "requestencapsulator.h"
#include "chartbuilder.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, const InitialAccountSetup* initAccountSetup =nullptr, const SymbolTernarySearchTree *pSymbolTST = nullptr );
    MainWindow() = delete;
    MainWindow(const MainWindow & window) = delete;
    MainWindow & operator = (const MainWindow & window) = delete;
    ~MainWindow();

    enum class Status
    {
        NotStarted,
        Working,
        NewSimulation,
        LoadSimulation,
        ExitNormal,
        ExitError
    };

private:
    void refreshSymbolInformation();
    void showViewSymbolPage();

private slots:
    void on_symbolSearchLineEdit_textChanged(const QString &arg1);
    void on_symbolListResults_clicked(const QModelIndex &index);
    void on_symbolSearchLineEdit_returnPressed();
    void on_searchSymbolButton_clicked();

private:
    QStandardItemModel model;
    Ui::MainWindow *ui;
    Account * pAccount;
    RequestEncapsulator requestEncapsulator;
    const SymbolTernarySearchTree * pSymbolTST;
    QVector<const SymbolTernarySearchTree::Node *> vSearchResults;
    ChartBuilder chartBuilder;
};
#endif // MAINWINDOW_H
