#ifndef SYMBOLBST_H
#define SYMBOLBST_H
#include <symbol.h>

class SymbolBST
{
public:
    SymbolBST();
    SymbolBST(Symbol *pSymbol);
    SymbolBST(const SymbolBST & assign) =delete;
    SymbolBST & operator =(const SymbolBST & assign)= delete;
    ~SymbolBST() =default;

    void insert(SymbolBST *pRoot, Symbol *pItem);
    void print(SymbolBST *pRoot);
private:
    SymbolBST *pRight, *pLeft;
    Symbol *pSymbol;
};

#endif // SYMBOLBST_H
