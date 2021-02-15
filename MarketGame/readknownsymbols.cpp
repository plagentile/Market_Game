#include "readknownsymbols.h"

ReadKnownSymbols::ReadKnownSymbols()
    :symStatus(Status::Normal), pSymbolTernarySearchTree(new SymbolTernarySearchTree())
{
}

ReadKnownSymbols::~ReadKnownSymbols(){
    delete pSymbolTernarySearchTree;
}

ReadKnownSymbols::Status ReadKnownSymbols::run(){
    QElapsedTimer timer;
    timer.start();

   this->readKnownSymbolsFile();
   printf("\nTime taken: %lli\n", timer.elapsed());
   return this->symStatus;
}

const SymbolTernarySearchTree *ReadKnownSymbols::getSymbolTernarySearchTree() const noexcept{
    return this->pSymbolTernarySearchTree;
}

void ReadKnownSymbols::readKnownSymbolsFile() noexcept{
    QFile file(":/files/coreData/unsortedKnownSymbolsCommaSeperated.csv");
    if(!file.exists()){
        this->symStatus =Status::FileNotFound;
        return;
    }
    if(!file.open(QIODevice::ReadOnly) ){
        this->symStatus =Status::CouldNotOpenFile;
        return;
    }
    QTextStream stream(&file);
    while(!stream.atEnd()){
        this->pSymbolTernarySearchTree->insert(std::move(stream.readLine().split(',')));
    }
    file.close();
}








