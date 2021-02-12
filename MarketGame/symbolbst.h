#ifndef SYMBOLBST_H
#define SYMBOLBST_H

#include<QString>
#include <QStringList>
#include <future>
class SymbolBST{

public:
    struct Node{

        Node(const QStringList&& val) noexcept
            :pLeft(0), pRight(0), symbol(std::move(val[0])), name(std::move(val[1])), country(std::move(val[2])),
              sector(std::move(val[3])), industry(std::move(val[4]))
        {
        }
        /*Check other operators*/
        Node() = delete;
        Node(const Node &rhs) = delete;
        Node & operator = (const Node &rhs) = delete;
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

    void insert(Node *pNode) noexcept;
    const QStringList search(const QString symbol) const noexcept;

private:
    Node *pRoot;
    std::mutex rootMutex;
};

#endif // SYMBOLBST_H
