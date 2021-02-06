#include "readknownsymbols.h"

//Total file size is 5656 lines
#define MAX_FILE_LINE_SIZE 5656

ReadKnownSymbols::ReadKnownSymbols()
    :pQStringQueue(new SingleUseQStringQueue(MAX_FILE_LINE_SIZE)), pSymbolBST(new SymbolBST())
{
}

ReadKnownSymbols::~ReadKnownSymbols(){
    delete pSymbolBST;
}

void ReadKnownSymbols::run(){
   std::thread t_ReadSymbolFileThread(&ReadKnownSymbols::readKnownSymbolsFile, this);
   t_ReadSymbolFileThread.detach();

   std::thread t_ConvertSymbols(&ReadKnownSymbols::convertFileStrings, this);
   t_ConvertSymbols.detach();
}

void ReadKnownSymbols::readKnownSymbolsFile()
{
    QFile file(":/files/coreData/knownSymbolsUnsortedCommaSeperated.csv");

    if(!file.exists()){
        printf("FILE NOT FOUND");
        return;
    }
     if(!file.open(QIODevice::ReadOnly)){
        printf("COULD NOT OPEN THE FILE");
        return;
    }

     //Read Line by Line
     uint32_t x =0;

     while (!file.atEnd() && x < MAX_FILE_LINE_SIZE) {
            this->pQStringQueue->enqueueMove(std::move(file.readLine()));
            x++;
     }

     file.close();
}

void ReadKnownSymbols::convertFileStrings(){

    QElapsedTimer timer;
    timer.start();

    for(uint32_t x = 0; x < MAX_FILE_LINE_SIZE; x++){
        QStringList list = this->pQStringQueue->dequeue().split(',');

        SymbolBST::Node *pNode = new SymbolBST::Node(list[0], list[1],list[2],list[3],list[4]);//this
        this->pSymbolBST->insert(pNode);

    }
    printf("\nDuration in time:%lli\n", timer.elapsed());
}

void ReadKnownSymbols::print() const{
    this->pSymbolBST->print(this->pSymbolBST->getRoot());
}












