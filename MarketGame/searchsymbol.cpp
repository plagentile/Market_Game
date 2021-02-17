#include "searchsymbol.h"
#include "ui_searchsymbol.h"

SearchSymbol::SearchSymbol(QWidget *parent, const SymbolTernarySearchTree *symbolTST) :
    QDialog(parent),
    ui(new Ui::SearchSymbol),
    pSymbolTernarySearchTree(symbolTST)
{
    ui->setupUi(this);

    model.setColumnCount(4);
    model.setHorizontalHeaderLabels({"Symbol", "Name", "Sector", "Industry"});
}

SearchSymbol::~SearchSymbol(){
    delete ui;
}

void SearchSymbol::run(){
    this->exec();
}

/*User is searching a symbol*/
void SearchSymbol::on_symbolLineEdit_textChanged(const QString &arg1){
    model.removeRows(0, model.rowCount());
    if(arg1.length() < 0 || arg1.length() > 5) return;

    QVector<const SymbolTernarySearchTree::Node *> vectRes = this->pSymbolTernarySearchTree->searchTST(arg1);
    const int32_t length = vectRes.length();
    model.insertRows(0, length);
    for(int32_t r =0 ; r < length; ++r){
        model.setItem(r,0, new QStandardItem(vectRes[r]->symbol));
        model.setItem(r,1, new QStandardItem(vectRes[r]->name));
        model.setItem(r,2, new QStandardItem(vectRes[r]->sector));
        model.setItem(r,3, new QStandardItem(vectRes[r]->industry));
    }
    ui->tableView->setModel(&model);
}
