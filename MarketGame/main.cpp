#include "Coordinator.h"
#include "symbolternarysearchtree.h"
#include "networkhandler.h"

int32_t main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Coordinator  coordinator(nullptr);
    coordinator.run();
    return a.exec();
}
