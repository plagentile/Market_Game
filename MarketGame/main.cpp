#include <QApplication>
#include "Coordinator.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Coordinator * pCoordinator = Coordinator::getInstance();
    pCoordinator->run();    
    int num = a.exec();

    /*Ensure that leaks are plugged*/
    delete pCoordinator;
    return num;
}
