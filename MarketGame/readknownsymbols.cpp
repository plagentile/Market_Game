#include "readknownsymbols.h"

ReadKnownSymbols::ReadKnownSymbols()
    :symStatus(Status::Working), pSymbolTernarySearchTree(new SymbolTernarySearchTree())
{
}

ReadKnownSymbols::~ReadKnownSymbols(){
    delete pSymbolTernarySearchTree;
}

void ReadKnownSymbols::run() noexcept{
    this->symStatus = this->readKnownSymbolsFile();
}

const SymbolTernarySearchTree *ReadKnownSymbols::getSymbolTernarySearchTree() const noexcept{
    return this->pSymbolTernarySearchTree;
}

ReadKnownSymbols::Status ReadKnownSymbols::getStatus() const noexcept{
    return this->symStatus;
}

ReadKnownSymbols::Status ReadKnownSymbols::readKnownSymbolsFile() noexcept{
    QFile file(":/files/coreData/unsortedKnownSymbolsCommaSeperated.csv");
    if(!file.exists()){
        return Status::FileNotFound;
    }
    if(!file.open(QIODevice::ReadOnly) ){
        return Status::CouldNotOpenFile;
    }
    QTextStream stream(&file);
    while(!stream.atEnd()){
        this->pSymbolTernarySearchTree->insert(std::move(stream.readLine().split(',')));
    }
    file.close();
    return Status::Done;
}








