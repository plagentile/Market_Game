#ifndef SYMBOLBST_H
#define SYMBOLBST_H

#include<QString>
class SymbolBST{

public:
    struct Node{
        Node(const QString symbol, const QString name, const QString country, const QString sector, const QString industry)
             :pLeft(0), pRight(0), symbol(symbol), name(name), country(country), sector(sector), industry(industry)
        {
        }
        /*Check other operators*/
        Node() = delete;
        ~Node()
        {
            delete pLeft;
            delete pRight;
        }
        Node *pLeft;
        Node *pRight;
        const QString symbol;
        const QString name;
        const QString country;
        const QString sector;
        const QString industry;
    };

public:
    SymbolBST();
    SymbolBST(const SymbolBST & assign) =delete;
    SymbolBST & operator =(const SymbolBST & assign)= delete;
    ~SymbolBST();

    void insert(Node *pNode);
    void print(Node *pRoot);
    Node * getRoot();
private:
    Node *pRoot;
};

#endif // SYMBOLBST_H
