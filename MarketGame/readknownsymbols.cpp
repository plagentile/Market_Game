#include "readknownsymbols.h"

//Total file size is 5651 lines
#define MAX_FILE_LINE_SIZE 5561

ReadKnownSymbols::ReadKnownSymbols()
    :pQStringQueue(new SingleUseQStringQueue(MAX_FILE_LINE_SIZE)), pSymbolTernarySearchTree(new SymbolTernarySearchTree()), syncDequeuing(-1), symStatus(Status::Normal)
{
}

ReadKnownSymbols::~ReadKnownSymbols(){
    delete pSymbolTernarySearchTree;
    delete pQStringQueue;
}

ReadKnownSymbols::Status ReadKnownSymbols::run(){

   QElapsedTimer timer;
   timer.start();

   std::thread t_ReadSymbolFileThreadOne(&ReadKnownSymbols::readKnownSymbolsFile, this);
   t_ReadSymbolFileThreadOne.detach();


   std::thread t_ConvertSymbolsTwo(&ReadKnownSymbols::convertFileStrings, this);
   t_ConvertSymbolsTwo.join();

   printf("\nTime taken..: %lli\n", timer.elapsed());
   return this->symStatus;
}

const SymbolTernarySearchTree *ReadKnownSymbols::getSymbolTernarySearchTree() const noexcept{
    return this->pSymbolTernarySearchTree;
}

void ReadKnownSymbols::readKnownSymbolsFile() noexcept
{
    QFile file(":/files/coreData/unsortedKnownSymbolsCommaSeperated.csv");
    if(!file.exists()){
        this->symStatus =Status::FileNotFound;
        return;
    }
    if(!file.open(QIODevice::ReadOnly) ){
        this->symStatus =Status::CouldNotOpenFile;
        return;
    }
     while (!file.atEnd()){
        this->pQStringQueue->enqueueMove(std::move(file.readLine()));
     }
     file.close();
}

void ReadKnownSymbols::convertFileStrings() {
    while(++syncDequeuing < MAX_FILE_LINE_SIZE && symStatus == Status::Normal)
    {
        QStringList list = this->pQStringQueue->dequeue().split(',');
        this->pSymbolTernarySearchTree->insert(list[0], list);
    }
}








