#ifndef READKNOWNSYMBOLS_H
#define READKNOWNSYMBOLS_H
#include "singleuseqstringqueue.h"
#include "symbolternarysearchtree.h"
#include <QFile>
#include <QElapsedTimer>
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
    void convertFileStrings();
private:
    SingleUseQStringQueue * pQStringQueue;
    SymbolTernarySearchTree *pSymbolTernarySearchTree;
    std::atomic_uint32_t syncDequeuing;
    std::atomic<Status> symStatus;

};

#endif // READKNOWNSYMBOLS_H
