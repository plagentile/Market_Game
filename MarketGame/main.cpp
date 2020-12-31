#include <QApplication>
#include "Coordinator.h"
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Coordinator & pCoordinator = *(Coordinator::getInstance());
    pCoordinator.run();
    return a.exec();
}
