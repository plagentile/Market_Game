#include "readknownsymbols.h"

ReadKnownSymbols::ReadKnownSymbols()
    :symStatus(Status::Working)
{
}

void ReadKnownSymbols::run() {
    this->symStatus = this->readKnownSymbolsFile();
}

const SymbolTernarySearchTree *ReadKnownSymbols::getSymbolTernarySearchTree() const noexcept{
    return &this->symbolTernarySearchTree;
}

ReadKnownSymbols::Status ReadKnownSymbols::getStatus() const noexcept{
    return this->symStatus;
}

ReadKnownSymbols::Status ReadKnownSymbols::readKnownSymbolsFile() {
    QFile file(":/files/coreData/unsortedKnownSymbolsCommaSeperated.csv");
    if(!file.exists()){
        return Status::FileNotFound;
    }
    if(!file.open(QIODevice::ReadOnly) ){
        return Status::CouldNotOpenFile;
    }
    QTextStream stream(&file);
    while(!stream.atEnd()){
        this->symbolTernarySearchTree.insert(stream.readLine().split(','));
    }
    file.close();
    return Status::Done;
}


