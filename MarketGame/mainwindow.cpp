#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, const InitialAccountSetup* initAccountSetup, const SymbolTernarySearchTree *pSymbolTST)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      pAccount(new Account(0, initAccountSetup->getInitBalance(), initAccountSetup->getAPIKey())),
      pSymbolTST(pSymbolTST)
{
    this->ui->setupUi(this);
    this->ui->symbolSearchLineEdit->setValidator(new QRegExpValidator(QRegExp("[A-Z]{0,4}"), 0));
    this->ui->symbolListResults->hide();                                                                            //Hide list of recommendations initially
}

MainWindow::~MainWindow(){
    delete ui;
    delete pAccount;
}


void MainWindow::refresh(){
    this->ui->dynamicAccountBalanceLabel->setText(QString::number(this->pAccount->getAccountBalance(), 'f', 2));
    this->ui->dynamicAvailableFundsLabel->setText(QString::number(this->pAccount->getAvailableFunds(), 'f', 2));
}

void MainWindow::on_symbolSearchLineEdit_textChanged(const QString &arg1){
    if(arg1.length() <= 0) return;
    if(this->ui->symbolListResults->isHidden()) this->ui->symbolListResults->show();                                //Show the recommendations only if we have valid input

    QVector<const SymbolTernarySearchTree::Node *> vectRes = this->pSymbolTST->searchTST(arg1);
    const int32_t length = vectRes.length();
    if(length == 0) return;                                                                                         //Keep previous recommendations if going down a non existant symbol path

    QStandardItem *pRoot = model.invisibleRootItem();
    pRoot->removeRows(0, model.rowCount());

    for(int32_t r =0 ; r < length; ++r){
        pRoot->appendRow(new QStandardItem(vectRes[r]->symbol +", " +vectRes[r]->name + ", " +vectRes[r]->industry));
    }
    ui->symbolListResults->setModel(&model);
}

void MainWindow::on_symbolListResults_clicked(const QModelIndex &index){                                              //User clicked on a recommendation in the symbol list results fill the line edit, hide other recommendations
    QStandardItem * item = this->model.itemFromIndex(index);

    /*Find the symbol in the string*/
    if(item){
        QString res = item->data(0).toString();
        QString temp = "";
        for(int x = 0; x < res.length(); ++x){
            if(res[x] == ',') break;
            temp += res[x];
        }
        this->ui->symbolSearchLineEdit->setText(temp);
        this->ui->symbolListResults->hide();
    }
}


void MainWindow::on_symbolSearchLineEdit_returnPressed(){
    printf("\nClicked enter with: %ls", qUtf16Printable(this->ui->symbolSearchLineEdit->text()));
}
