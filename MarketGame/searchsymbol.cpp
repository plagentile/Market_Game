#include "searchsymbol.h"
#include "ui_searchsymbol.h"

SearchSymbol::SearchSymbol(QWidget *parent, const SymbolTernarySearchTree *symbolTST) :
    QDialog(parent),
    ui(new Ui::SearchSymbol),
    pSymbolTernarySearchTree(symbolTST)
{
    ui->setupUi(this);
    if(this->pSymbolTernarySearchTree){
        printf("\nValid");
    }
}

SearchSymbol::~SearchSymbol()
{
    delete ui;
}

void SearchSymbol::run()
{
    this->exec();
}

/*User is searching a symbol*/
void SearchSymbol::on_symbolLineEdit_textChanged(const QString &arg1)
{
    if(arg1 != "")
    {
        QStringList list = this->pSymbolTernarySearchTree->searchTST(arg1);
        for(int x =0; x < list.length(); x++){
             printf("\nSEARCH RES: %ls", qUtf16Printable(list[x]));
        }
    }
    printf("\n");
}
