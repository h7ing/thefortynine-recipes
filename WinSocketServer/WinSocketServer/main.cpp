#include <iostream>
#include <memory>
#include "SocketServer.h"

int main() {
    startDebugServer();
    std::cout << "main\n";
    std::cout << std::endl;
    std::cin.ignore();
    return 0;
}
