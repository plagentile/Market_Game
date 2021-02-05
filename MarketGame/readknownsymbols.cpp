#include "readknownsymbols.h"

ReadKnownSymbols::ReadKnownSymbols()
    :pQStringQueue(new SingleUseQStringQueue(MAX_FILE_LINE_SIZE))
{
}

ReadKnownSymbols::~ReadKnownSymbols()
{
    //wait for threads...
}

void ReadKnownSymbols::run(){
   QElapsedTimer timer;
   timer.start();

   std::thread t_ReadSymbolFileThread(&ReadKnownSymbols::readKnownSymbolsFile, this);
   std::thread t_ConvertSymbols(&ReadKnownSymbols::convertFileStrings, this);
   t_ReadSymbolFileThread.join();
   t_ConvertSymbols.join();

   printf("\nDuration in time:%lli\n", timer.elapsed());
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
            this->pQStringQueue->enqueue(std::move(file.readLine()));
            x++;
     }

     file.close();
}

void ReadKnownSymbols::convertFileStrings(){
    for(uint32_t x = 0; x < MAX_FILE_LINE_SIZE; x++)
    {
        this->pQStringQueue->dequeue();
       //printf("Dequeue: %ls", qUtf16Printable(this->pQStringQueue->dequeue()));

    }
}











