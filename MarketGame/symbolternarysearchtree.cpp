#include "symbolternarysearchtree.h"

SymbolTernarySearchTree::SymbolTernarySearchTree()
    :pRoot(0)
{
}

SymbolTernarySearchTree::~SymbolTernarySearchTree(){
    delete this->pRoot;
}

const QVector<const SymbolTernarySearchTree::Node*> SymbolTernarySearchTree::searchTST(const QString str) const{

    QVector<const SymbolTernarySearchTree::Node*> vectRes;
    if(!this->pRoot || str.length() == 0) return vectRes;
    vectRes.reserve(4);

    const int32_t strLength = str.length();
    int32_t strIndex = 0;
    int32_t vectIndex = 0;

    Node *pTemp = this->pRoot;
    QString res ="";
    while(pTemp && strIndex < strLength)
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
            res+= (pTemp->cData);
            if(res == str)
            {
                if(pTemp->completesSymbol){
                    vectRes.insert(vectIndex++,pTemp);
                }
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
            }
            pTemp = pTemp->pMid;
            ++strIndex;
        }
    }
    return vectRes;
}

void SymbolTernarySearchTree::insert(const QStringList &&list){
    if(list.size() ^ 0x4) return;     //ensure that there are ONLY 4 elements in the list
    this->insert(&this->pRoot, list[0], 0, list);
}

void SymbolTernarySearchTree::insert(SymbolTernarySearchTree::Node **root, const QString str, const int32_t strIndex, const QStringList &list )
{
    if(!(*root)){
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
        if((strIndex+1) < str.length()){
            insert(&((*root)->pMid), str, strIndex +1, list);
        }
        else{
            (*root)->completesSymbol = true;
            (*root)->symbol = list[0];
            (*root)->name = list[1];
            (*root)->sector = list[2];
            (*root)->industry = list[3];
        }
    }
}
