#include "readknownsymbols.h"

//Total file size is 5651 lines
#define MAX_FILE_LINE_SIZE 5561

ReadKnownSymbols::ReadKnownSymbols()
    :pQStringQueue(new SingleUseQStringQueue(MAX_FILE_LINE_SIZE)), pSymbolBST(new SymbolBST()), syncDequeuing(-1), symStatus(Status::Normal)
{
}

ReadKnownSymbols::~ReadKnownSymbols(){
    delete pSymbolBST;
    delete pQStringQueue;
}

ReadKnownSymbols::Status ReadKnownSymbols::run(){

   QElapsedTimer timer;
   timer.start();

   std::thread t_ReadSymbolFileThreadOne(&ReadKnownSymbols::readKnownSymbolsFile, this);
   t_ReadSymbolFileThreadOne.detach();

   std::thread t_ConvertSymbolsOne(&ReadKnownSymbols::convertFileStrings, this);
   std::thread t_ConvertSymbolsTwo(&ReadKnownSymbols::convertFileStrings, this);

   t_ConvertSymbolsOne.join();
   t_ConvertSymbolsTwo.join();

   printf("\nTime taken..: %lli\n", timer.elapsed());
   return this->symStatus;
}

QStringList ReadKnownSymbols::searchSymbols(QString string){
    return this->pSymbolBST->search(string);
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

void ReadKnownSymbols::convertFileStrings() noexcept{
    while(++syncDequeuing < MAX_FILE_LINE_SIZE && symStatus == Status::Normal){
        SymbolBST::Node *pNode = new SymbolBST::Node(std::move(this->pQStringQueue->dequeue().split(',')));
        this->pSymbolBST->insert(pNode);
    }
}












