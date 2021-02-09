#include "readknownsymbols.h"

//Total file size is 5656 lines
#define MAX_FILE_LINE_SIZE 5561

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

   QFile file(":/files/coreData/unsortedKnownSymbolsCommaSeperated.csv");

   std::thread t_ReadSymbolFileThreadOne(&ReadKnownSymbols::readKnownSymbolsFile, this, std::ref(file));
   t_ReadSymbolFileThreadOne.detach();

   std::thread t_ConvertSymbolsOne(&ReadKnownSymbols::convertFileStrings, this);
   std::thread t_ConvertSymbolsTwo(&ReadKnownSymbols::convertFileStrings, this);

   t_ConvertSymbolsOne.join();
   t_ConvertSymbolsTwo.join();

   printf("\nTime taken..: %lli\n", timer.elapsed());
}

QStringList ReadKnownSymbols::searchSymbols(QString string){
    return this->pSymbolBST->search(string);
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












