#include "Coordinator.h"

int32_t main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Coordinator * pCoordinator = Coordinator::getInstance();
    int32_t num = pCoordinator->run(a);
    delete pCoordinator;                                        //Ensure that leaks are plugged
    return num;
}
