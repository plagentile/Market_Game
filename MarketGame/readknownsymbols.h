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

    void run();
private:
    void readKnownSymbolsFile(QFile& file) noexcept;
    void convertFileStrings() noexcept;

private:
    SingleUseQStringQueue * pQStringQueue;
    SymbolBST *pSymbolBST;
    std::atomic_uint32_t syncDequeuing;
};

#endif // READKNOWNSYMBOLS_H
