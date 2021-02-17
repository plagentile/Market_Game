#ifndef SEARCHSYMBOL_H
#define SEARCHSYMBOL_H

#include <QDialog>
#include "symbolternarysearchtree.h"
#include <QStandardItemModel>
#include <QElapsedTimer>
namespace Ui {
class SearchSymbol;
}

class SearchSymbol : public QDialog
{
    Q_OBJECT

public:
    explicit SearchSymbol(QWidget *parent = nullptr, const SymbolTernarySearchTree *symbolTST = nullptr);
    SearchSymbol() = delete;
    SearchSymbol(const SearchSymbol& assign) = delete;
    SearchSymbol & operator =(const SearchSymbol & assign) = delete;
    ~SearchSymbol();

    void run();
private slots:
    void on_symbolLineEdit_textChanged(const QString &arg1);

private:
    Ui::SearchSymbol *ui;
    const SymbolTernarySearchTree *pSymbolTernarySearchTree;
    QStandardItemModel model;
};

#endif // SEARCHSYMBOL_H
