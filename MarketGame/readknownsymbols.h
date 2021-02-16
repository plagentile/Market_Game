#ifndef READKNOWNSYMBOLS_H
#define READKNOWNSYMBOLS_H
#include "symbolternarysearchtree.h"
#include <QFile>
#include <QTextStream>
#include <QElapsedTimer>
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

    void run() noexcept;

public:
    const SymbolTernarySearchTree * getSymbolTernarySearchTree() const noexcept;
    Status getStatus() const noexcept;
private:
    Status readKnownSymbolsFile() noexcept;
private:
    Status symStatus;
    SymbolTernarySearchTree *pSymbolTernarySearchTree;
};

#endif // READKNOWNSYMBOLS_H
