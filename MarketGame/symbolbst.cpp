#include "symbolbst.h"

SymbolBST::SymbolBST()
    :pRight(0), pLeft(0)
{
}

SymbolBST::SymbolBST(Symbol *pSymbol)
    :pRight(0), pLeft(0), pSymbol(pSymbol)
{
}

void SymbolBST::insert(SymbolBST *pRoot, Symbol *pItem){

    if(!pRoot){
        printf("\nInserting: %ls, at root", qUtf16Printable(pItem->name));
        pRoot = new SymbolBST(pItem);
        return;
    }

   //Make new item to be inserted
   SymbolBST *pParent = nullptr;
   SymbolBST *pCurrent = pRoot;

   while(pCurrent){
       pParent = pCurrent;
       if(pCurrent->pSymbol->symbol > pItem->symbol){
           pCurrent = pCurrent->pLeft;
       }
       else{
           pCurrent = pCurrent->pRight;
       }
   }

   if(pParent->pSymbol->symbol > pItem->symbol){
        printf("Inserting: %ls, to the left of: %ls\n", qUtf16Printable(pItem->symbol), qUtf16Printable(pParent->pSymbol->symbol));
        pParent->pLeft = new SymbolBST(pItem);
   }
   else{
       printf("Inserting: %ls, to the right of: %ls\n", qUtf16Printable(pItem->symbol), qUtf16Printable(pParent->pSymbol->symbol));
       pParent->pRight = new SymbolBST(pItem);
  }
}

void SymbolBST::print(SymbolBST *pRoot)
{
    if(pRoot == nullptr){
        return;
    }
    print(pRoot->pLeft);
    printf("Order: %ls\n", qUtf16Printable(pRoot->pSymbol->symbol));
    print(pRoot->pRight);
}
