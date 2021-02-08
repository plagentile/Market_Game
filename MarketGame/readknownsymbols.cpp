#include "readknownsymbols.h"

//Total file size is 5656 lines
#define MAX_FILE_LINE_SIZE 5656

ReadKnownSymbols::ReadKnownSymbols()
    :pQStringQueue(new SingleUseQStringQueue(MAX_FILE_LINE_SIZE)), pSymbolBST(new SymbolBST()), syncDequeuing(-1)
{
}

ReadKnownSymbols::~ReadKnownSymbols(){
    delete pSymbolBST;
    delete pQStringQueue;
}

void ReadKnownSymbols::run(){   

   QElapsedTimer timer;
   timer.start();

   QFile file_1(":/files/coreData/unsortedKnownSymbolsCommaSeperated_1.csv");
   QFile file_2(":/files/coreData/unsortedKnownSymbolsCommaSeperated_2.csv");

   std::thread t_ReadSymbolFileThreadOne(&ReadKnownSymbols::readKnownSymbolsFile, this, std::ref(file_1));
   t_ReadSymbolFileThreadOne.detach();

   std::thread t_ReadSymbolFileThreadTwo(&ReadKnownSymbols::readKnownSymbolsFile, this, std::ref(file_2));
   t_ReadSymbolFileThreadTwo.detach();

   std::thread t_ConvertSymbols(&ReadKnownSymbols::convertFileStrings, this);
   std::thread t_ConvertSymbolsTwo(&ReadKnownSymbols::convertFileStrings, this);


   t_ConvertSymbols.join();
   t_ConvertSymbolsTwo.join();
   printf("\nTime taken: %lli\n", timer.elapsed());
}

void ReadKnownSymbols::readKnownSymbolsFile(QFile& file) noexcept
{
    if(!file.exists() || !file.open(QIODevice::ReadOnly) ){
        return;
    }
     while (!file.atEnd()){
        this->pQStringQueue->enqueueMove(std::move(file.readLine()));
     }
     if(file.isOpen())file.close();
}

void ReadKnownSymbols::convertFileStrings() noexcept{
    while(++syncDequeuing < MAX_FILE_LINE_SIZE){
        SymbolBST::Node *pNode = new SymbolBST::Node(std::move(this->pQStringQueue->dequeue().split(',')));
        this->pSymbolBST->insert(pNode);
    }
}












