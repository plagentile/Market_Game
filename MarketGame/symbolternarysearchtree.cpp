#include "symbolternarysearchtree.h"

SymbolTernarySearchTree::SymbolTernarySearchTree()
    :pRoot(0)
{
}

SymbolTernarySearchTree::~SymbolTernarySearchTree(){
    delete this->pRoot;
}

const QVector<SymbolTernarySearchTree::Node*> SymbolTernarySearchTree::searchTST(const QString str) const{

    QVector<SymbolTernarySearchTree::Node*> vectRes;
    if(!this->pRoot || str.length() == 0) return vectRes;
    vectRes.reserve(4);
    int strIndex = 0;
    int vectIndex = 0;
    Node *pTemp = this->pRoot;
    QString res ="";

    while(pTemp && strIndex < str.length())
    {
        if(pTemp->cData > str[strIndex]){
            pTemp = pTemp->pLeft;
        }
        else if(pTemp->cData < str[strIndex]){
            pTemp = pTemp->pRight;
        }
        else
        {
            //hit, follow the chain
            res.append(pTemp->cData);
            if(res == str)
            {
                if(pTemp->completesSymbol)
                {
                    //successful query, return the item
                    vectRes.insert(vectIndex++,pTemp);

                    //before returning, look one deep in each direction
                    if(pTemp->pLeft && pTemp->pLeft->completesSymbol){
                         vectRes.insert(vectIndex++,pTemp->pLeft);
                    }
                    if(pTemp->pMid && pTemp->pMid->completesSymbol){
                         vectRes.insert(vectIndex++,pTemp->pMid);
                    }
                    if(pTemp->pRight && pTemp->pRight->completesSymbol){
                         vectRes.insert(vectIndex++,pTemp->pRight);
                    }
                    return vectRes;
                }
                else
                {
                    //Incomplete search query, look down the line to where completed string may be
                    if(pTemp->pLeft && pTemp->pLeft->completesSymbol){
                         vectRes.insert(vectIndex++,pTemp->pLeft);
                    }
                    if(pTemp->pMid && pTemp->pMid->completesSymbol){
                         vectRes.insert(vectIndex++,pTemp->pMid);
                    }
                    if(pTemp->pRight && pTemp->pRight->completesSymbol){
                         vectRes.insert(vectIndex++,pTemp->pRight);
                    }
                }
            }
            pTemp = pTemp->pMid;
            strIndex++;
        }
    }
    return vectRes;
}

void SymbolTernarySearchTree::insert(const QString str, const QStringList &list){
    if(str == "") return;
    this->insert(&this->pRoot, str, 0, list);
}

void SymbolTernarySearchTree::insert(SymbolTernarySearchTree::Node **root, const QString str, const int32_t strIndex, const QStringList &list )
{
    if(!(*root))
    {
        if(strIndex == str.length() -1){
            *root = new Node(str[strIndex], list);
            return;
        }
        *root = new Node(str[strIndex]);
    }

    if((str[strIndex]) < (*root)->cData){
        insert(&((*root)->pLeft), str, strIndex, list);
    }

    else if((str[strIndex]) > (*root)->cData){
        insert(&((*root)->pRight), str, strIndex, list);
    }

    else{
        if((strIndex +1) < str.length()){
            insert(&((*root)->pMid), str, strIndex+1, list);
        }
        else{
            (*root)->completesSymbol = true;
            (*root)->name =list[1];
        }
    }
}

