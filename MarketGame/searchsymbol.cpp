#include "searchsymbol.h"
#include "ui_searchsymbol.h"

SearchSymbol::SearchSymbol(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchSymbol)
{
    ui->setupUi(this);
}

SearchSymbol::~SearchSymbol()
{
    delete ui;
}

/*User is searching a symbol*/
void SearchSymbol::on_symbolLineEdit_textChanged(const QString &arg1)
{

}
