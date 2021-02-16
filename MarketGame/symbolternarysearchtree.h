#ifndef SYMBOLTERNARYSEARCHTREE_H
#define SYMBOLTERNARYSEARCHTREE_H
#include <QStringList>
#include <QVector>
class SymbolTernarySearchTree
{

public:
    struct Node
    {
        Node(QChar cData)
            :cData(cData), pMid(0), pLeft(0), pRight(0),completesSymbol(false)
        {
        }
        Node(QChar cData, const QStringList &list)
           :cData(cData), pMid(0), pLeft(0), pRight(0), completesSymbol(true),symbol(list[0]),
             name(list[1]), country(list[2]), sector(list[3]), industry(list[4])
        {
        }
        Node() = delete;
        Node(const Node & assign) = delete;
        Node & operator =(const Node& assign) =delete;
        ~Node()
        {
            delete pLeft;
            delete pMid;
            delete pRight;
        }
        QChar cData;
        Node *pMid;
        Node *pLeft;
        Node *pRight;

        bool completesSymbol;
        QString symbol;
        QString name;
        QString country;
        QString sector;
        QString industry;
    };

public:
    SymbolTernarySearchTree();
    SymbolTernarySearchTree(const SymbolTernarySearchTree & assign) = delete;
    SymbolTernarySearchTree & operator =(const SymbolTernarySearchTree & assign) = delete;
    ~SymbolTernarySearchTree();

    const QVector<const Node*> searchTST(const QString str) const;
    void insert(const QStringList &&list);
private:
    void insert(Node** root, const QString str, const int32_t strIndex, const QStringList &list);
private:
   Node *pRoot;
};

#endif // SYMBOLTERNARYSEARCHTREE_H
