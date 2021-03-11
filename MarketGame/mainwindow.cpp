#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, const int32_t initBalance, const QString initAPIKey, const SymbolTernarySearchTree *pTST)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      pAccount(new Account(0, initBalance, initAPIKey)),
      pSymbolTST(pTST),
      status(Status::Normal)
{
    this->ui->setupUi(this);
    this->ui->symbolSearchLineEdit->setValidator(new QRegExpValidator(QRegExp("[A-Z]{0,4}"), 0));
    this->ui->symbolListResults->hide();                                                                              //Hide list of recommendations initially
    this->ui->searchSymbolButton->hide();
    vSearchResults.reserve(this->pSymbolTST->getSYMBOL_SEARCH_VECTOR_RESERVE_SIZE());
}


MainWindow::~MainWindow(){
    delete ui;
    delete pAccount;
}

void MainWindow::refreshSymbolInformation(){
    this->ui->dynamicAccountBalanceLabel->setText(QString::number(this->pAccount->getAccountBalance(), 'f', 2));
    this->ui->dynamicAvailableFundsLabel->setText(QString::number(this->pAccount->getAvailableFunds(), 'f', 2));
}

void MainWindow::showViewSymbolPage(){
    //Check if the current text exists in this->vectSearchResults;
    const QString currTextEdit = this->ui->symbolSearchLineEdit->text();
    for(int32_t x = 0, length = this->vSearchResults.length(); x < length; ++x){
        if(currTextEdit == vSearchResults[x]->symbol){
            //Valid symbol, set and show the next page, default view is one year of data with price points set at once per week
            //this->ui->graphicsView->setChart(chartBuilder.buildLineChart(this))
            this->requestEncapsulator.getPriceHistory(this->pAccount->getAPIKey(), currTextEdit, "year", 1, "weekly", 1);
            this->refreshSymbolInformation();
            this->ui->searchAndViewSymbolStackedWidget->setCurrentIndex(1);
        }
    }
}

void MainWindow::on_symbolSearchLineEdit_textChanged(const QString &arg1){
    if(arg1.length() <= 0) return;

    this->ui->searchSymbolButton->hide();
    this->ui->symbolListResults->show();

    this->vSearchResults = this->pSymbolTST->searchTST(arg1);                                                         //A move here would prevent RVO
    if(this->vSearchResults.length() == 0) return;                                                                    //Keep previous recommendations if going down a non existant symbol path

    QStandardItem *pRoot = model.invisibleRootItem();
    pRoot->removeRows(0, model.rowCount());

    for(int32_t r =0, length = this->vSearchResults.length(); r < length; ++r){
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
        for(int32_t x = 0, length = res.length(); x < length; ++x){
            if(res[x] == ',') break;
            temp += res[x];
        }
        this->ui->symbolSearchLineEdit->setText(temp);
        this->ui->symbolListResults->hide();
        this->ui->searchSymbolButton->show();
    }
}

void MainWindow::on_symbolSearchLineEdit_returnPressed(){
    this->showViewSymbolPage();
}

void MainWindow::on_searchSymbolButton_clicked(){
    this->showViewSymbolPage();
}

MainWindow::Status MainWindow::getStatus() const{
    return status;
}
