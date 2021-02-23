#ifndef SYMBOLTERNARYSEARCHTREE_H
#define SYMBOLTERNARYSEARCHTREE_H
#include <QStringList>
#include <QVector>
class SymbolTernarySearchTree
{

public:
    struct Node
    {
        Node(const QChar cData)
            :pLeft(0), pRight(0), pMid(0), cData(cData),completesSymbol(false)
        {
        }
        Node(const QChar cData, const QStringList &list)
           :pLeft(0), pRight(0), pMid(0), cData(cData), completesSymbol(true), symbol(list[0]),
             name(list[1]), industry(list[2])
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

        Node *pLeft;
        Node *pRight;
        Node *pMid;

        const QChar cData;
        bool completesSymbol;

        QString symbol;
        QString name;
        QString industry;
    };

public:
    SymbolTernarySearchTree();
    SymbolTernarySearchTree(const SymbolTernarySearchTree & assign) = delete;
    SymbolTernarySearchTree & operator =(const SymbolTernarySearchTree & assign) = delete;
    ~SymbolTernarySearchTree();

    const QVector<const Node*> searchTST(const QString& str) const;
    void insert(const QStringList&& list);
    int32_t getSYMBOL_SEARCH_VECTOR_RESERVE_SIZE() const;

private:
    void insert(Node** root, const QString& str, const int32_t strIndex, const QStringList& list);
    void continuePath(const Node* pAt, QVector<const Node*>& vec, int32_t& vecPos) const;
private:
   Node *pRoot;
   const int32_t SYMBOL_SEARCH_VECTOR_RESERVE_SIZE;
};

#endif // SYMBOLTERNARYSEARCHTREE_H
