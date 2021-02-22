#include "symbolternarysearchtree.h"

SymbolTernarySearchTree::SymbolTernarySearchTree()
    :pRoot(0), SYMBOL_SEARCH_VECTOR_RESERVE_SIZE(13)
{
}

SymbolTernarySearchTree::~SymbolTernarySearchTree(){
    delete this->pRoot;
}

const QVector<const SymbolTernarySearchTree::Node*> SymbolTernarySearchTree::searchTST(const QString str) const{

    QVector<const SymbolTernarySearchTree::Node*> vectRes;
    if(!this->pRoot || str.length() == 0) return vectRes;
    vectRes.reserve(SYMBOL_SEARCH_VECTOR_RESERVE_SIZE);

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
                if(pTemp->completesSymbol)
                    vectRes.insert(vectIndex++, pTemp);

                this->continuePath(pTemp->pLeft,vectRes,vectIndex );
                this->continuePath(pTemp->pMid, vectRes,vectIndex );
                this->continuePath(pTemp->pRight, vectRes,vectIndex );
            }
            pTemp = pTemp->pMid;
            ++strIndex;
        }
    }
    return vectRes;
}


void SymbolTernarySearchTree::continuePath(const SymbolTernarySearchTree::Node *pAt, QVector<const SymbolTernarySearchTree::Node *> &vec, int32_t &vecPos) const
{
    if(!pAt || (vecPos + 3 > vec.capacity())) return;  //current position + 3 (possible) additional checks = 4, so we are checking for 4 possible adds


    if(pAt->completesSymbol){
        vec.insert(vecPos++, pAt);
    }
    if(pAt->pLeft &&pAt->pLeft->completesSymbol){
        vec.insert(vecPos++, pAt->pLeft);
    }

    if(pAt->pMid && pAt->pMid->completesSymbol){
        vec.insert(vecPos++, pAt->pMid);
    }

    if(pAt->pRight && pAt->pRight->completesSymbol){
        vec.insert(vecPos++, pAt->pRight);
    }

}

int32_t SymbolTernarySearchTree::getSYMBOL_SEARCH_VECTOR_RESERVE_SIZE() const{
    return SYMBOL_SEARCH_VECTOR_RESERVE_SIZE;
}


void SymbolTernarySearchTree::insert(const QStringList &&list){
    if(list.size() ^ 0x3) return;     //ensure that there are ONLY 3 elements in the list
    this->insert(&this->pRoot, list[0], 0, list);
}

void SymbolTernarySearchTree::insert(SymbolTernarySearchTree::Node **root, const QString str, const int32_t strIndex, const QStringList &list)
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
            (*root)->industry = list[2];
        }
    }
}








