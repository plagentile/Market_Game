#include "symbolternarysearchtree.h"

SymbolTernarySearchTree::SymbolTernarySearchTree()
    :pRoot(0)
{
}

SymbolTernarySearchTree::~SymbolTernarySearchTree()
{
    delete this->pRoot;
}

const QStringList SymbolTernarySearchTree::searchTST(const QString str) const
{

    QStringList listRes;
    if(!this->pRoot || str.length() == 0) return listRes;


    QString res ="";
    int strIndex = 0;

    Node *pTemp = this->pRoot;
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
                    //successful query, return the string, may look down the line for similar words
                    listRes.append(res + "\t" + pTemp->name);
                    return listRes;
                }
                else
                {
                    //Incomplete search query, look down the line to where completed string may be
                    if(pTemp->pLeft && pTemp->pLeft->completesSymbol){
                        listRes.append(res + pTemp->pLeft->cData);
                    }
                    if(pTemp->pMid && pTemp->pMid->completesSymbol){
                        listRes.append(res + pTemp->pMid->cData);
                    }
                    if(pTemp->pRight && pTemp->pRight->completesSymbol){
                        listRes.append(res + pTemp->pRight->cData);
                    }
                }
            }
            pTemp = pTemp->pMid;
            strIndex++;
        }
    }
    return listRes;
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
            numAdds++;
            return;
        }
        *root = new Node(str[strIndex]);
        numAdds++;
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

