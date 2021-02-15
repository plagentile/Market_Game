#ifndef READKNOWNSYMBOLS_H
#define READKNOWNSYMBOLS_H
#include "symbolternarysearchtree.h"
#include <QElapsedTimer>
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
        Normal,
        FileNotFound,
        CouldNotOpenFile
    };

    Status run();

public:
    const SymbolTernarySearchTree * getSymbolTernarySearchTree() const noexcept;
private:
    void readKnownSymbolsFile() noexcept;
private:
    Status symStatus;
    SymbolTernarySearchTree *pSymbolTernarySearchTree;
};

#endif // READKNOWNSYMBOLS_H
