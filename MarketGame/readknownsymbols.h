#ifndef READKNOWNSYMBOLS_H
#define READKNOWNSYMBOLS_H
#include "singleuseqstringqueue.h"
#include <symbolbst.h>
#include <QElapsedTimer>
#include <QFile>

class ReadKnownSymbols
{
public:
    ReadKnownSymbols();
    ReadKnownSymbols(const ReadKnownSymbols & assign) =delete;
    ReadKnownSymbols & operator = (const ReadKnownSymbols & assign) = delete;
    ~ReadKnownSymbols();

    void run();
private:
    void readKnownSymbolsFile();
    void convertFileStrings();

    void print() const;
private:
    SingleUseQStringQueue * pQStringQueue;
    SymbolBST *pSymbolBST;
};

#endif // READKNOWNSYMBOLS_H
