#include "symbolbst.h"

SymbolBST::SymbolBST()
    :pRoot(0)
{
}

SymbolBST::~SymbolBST(){
    delete pRoot;
}

void SymbolBST::insert(Node *pItem) noexcept{
    if(!pItem){
        return;
    }

    std::lock_guard<std::mutex> lock(this->rootMutex);
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

/*
 * Used For when a user searches a symbol, and will return a list of
 * the symbol (if it exists) and also symbols that are "like" the entered
 * one
 */
QStringList SymbolBST::search(QString symbol){
    QStringList list;
    if(symbol == "" || this->pRoot == nullptr) return list;
    Node *pTemp = pRoot;

    while(pTemp)
    {
        if(pTemp->symbol > symbol)
        {
            if(!pTemp->pLeft)
            {
                //Need to go left, but cannot,so searching two deep on near nodes if possible
                list.append(pTemp->symbol);
                if(pTemp->pRight)
                {
                    list.append(pTemp->pRight->symbol);
                    if(pTemp->pRight->pLeft){
                       list.append(pTemp->pRight->pLeft->symbol);
                     }
                    if(pTemp->pRight->pRight){
                       list.append(pTemp->pRight->pRight->symbol);
                     }
                }
                return list;
            }
            pTemp = pTemp->pLeft;
        }
        else if(pTemp->symbol < symbol)
        {
            if(!pTemp->pRight)
            {
                //Need to go right, but cannot,so searching two deep on near nodes if possible
                list.append(pTemp->symbol);
                if(pTemp->pLeft)
                {
                   list.append(pTemp->pLeft->symbol);
                   if(pTemp->pLeft->pLeft){
                     list.append(pTemp->pLeft->pLeft->symbol);
                   }

                   if(pTemp->pLeft->pRight){
                     list.append(pTemp->pLeft->pRight->symbol);
                   }
                }
                return list;
            }
            pTemp = pTemp->pRight;
        }
        else
        {
            //direct hit;
            list.append(pTemp->symbol);
            if(pTemp->pLeft){
                list.append(pTemp->pLeft->symbol);
            }
            if(pTemp->pRight){
                list.append(pTemp->pRight->symbol);
            }
            break;
        }
    }
    return list;
}
