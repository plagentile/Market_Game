#include "symbolbst.h"

SymbolBST::SymbolBST()
    :pRoot(0)
{
}

SymbolBST::~SymbolBST(){
    delete pRoot;
}

void SymbolBST::insert(Node *pItem){

    if(!pRoot){
        pRoot = pItem;
        return;
    }

   //Make new item to be inserted
   Node *pParent = nullptr;
   Node *pCurrent = pRoot;

   while(pCurrent){
       pParent = pCurrent;
       if(pCurrent->symbol > pItem->symbol){
           pCurrent = pCurrent->pLeft;
       }
       else{
           pCurrent = pCurrent->pRight;
       }
   }

   if(pParent->symbol > pItem->symbol){
        pParent->pLeft = pItem;
   }
   else{
       pParent->pRight = pItem;
   }
}

void SymbolBST::print(SymbolBST::Node *pRoot)
{
    if(pRoot == nullptr){
        return;
    }

    print(pRoot->pLeft);
    printf("\n%ls", qUtf16Printable(pRoot->symbol));
    print(pRoot->pRight);
}

SymbolBST::Node *SymbolBST::getRoot(){
    return this->pRoot;
}
