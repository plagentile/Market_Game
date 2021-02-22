#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, const InitialAccountSetup* initAccountSetup, const SymbolTernarySearchTree *pSymbolTST)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      pAccount(new Account(0, initAccountSetup->getInitBalance(), initAccountSetup->getAPIKey())),
      pSymbolTST(pSymbolTST)
{
    this->ui->setupUi(this);
    this->ui->symbolSearchLineEdit->setValidator(new QRegExpValidator(QRegExp("[A-Z]{0,4}"), 0));
    this->ui->symbolListResults->hide();        //Hide list of recommendations initially
    vSearchResults.reserve(this->pSymbolTST->getSYMBOL_SEARCH_VECTOR_RESERVE_SIZE());
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

    this->vSearchResults = this->pSymbolTST->searchTST(arg1);                                                              //A move here would prevent RVO
    if(this->vSearchResults.length() == 0) return;                                                                         //Keep previous recommendations if going down a non existant symbol path

    QStandardItem *pRoot = model.invisibleRootItem();
    pRoot->removeRows(0, model.rowCount());

    for(int32_t r =0 ; r < this->vSearchResults.length(); ++r){
        pRoot->appendRow(new QStandardItem(vSearchResults[r]->symbol +", " +vSearchResults[r]->name + ", " +vSearchResults[r]->industry));
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
    //Check if the current text exists in this->vectSearchResults;
    for(int32_t x = 0; x < this->vSearchResults.length(); ++x){
        if(this->ui->symbolSearchLineEdit->text() == vSearchResults[x]->symbol){
            //Valid symbol, set and show the next page
            this->ui->searchAndViewSymbolStackedWidget->setCurrentIndex(1);
        }
    }
}

