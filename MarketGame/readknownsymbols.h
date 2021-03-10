#ifndef READKNOWNSYMBOLS_H
#define READKNOWNSYMBOLS_H
#include "symbolternarysearchtree.h"
#include <QFile>
#include <QTextStream>
class ReadKnownSymbols
{
public:
    ReadKnownSymbols();
    ReadKnownSymbols(const ReadKnownSymbols & assign) =delete;
    ReadKnownSymbols & operator = (const ReadKnownSymbols & assign) = delete;
    ~ReadKnownSymbols();

    enum class Status{
        Working,
        FileNotFound,
        CouldNotOpenFile,
        Done
    };



public:
    const SymbolTernarySearchTree * getSymbolTernarySearchTree() const noexcept;
    Status getStatus() const noexcept;
    void run();
private:
    Status readKnownSymbolsFile();
private:
    Status symStatus;
    SymbolTernarySearchTree *pSymbolTernarySearchTree;
};

#endif // READKNOWNSYMBOLS_H
