#ifndef READKNOWNSYMBOLS_H
#define READKNOWNSYMBOLS_H
#include "singleuseqstringqueue.h"
#include <symbolbst.h>
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
    const SymbolBST * getBST() const noexcept;

private:
    void readKnownSymbolsFile() noexcept;
    void convertFileStrings();
private:
    SingleUseQStringQueue * pQStringQueue;
    SymbolBST *pSymbolBST;
    std::atomic_uint32_t syncDequeuing;
    std::atomic<Status> symStatus;

};

#endif // READKNOWNSYMBOLS_H
