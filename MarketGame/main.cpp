#include "Coordinator.h"
#include "symbolternarysearchtree.h"
#include "networkhandler.h"

int32_t main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Coordinator  coordinator(nullptr);
    const int32_t num = coordinator.run(&a);
    return num;
}
