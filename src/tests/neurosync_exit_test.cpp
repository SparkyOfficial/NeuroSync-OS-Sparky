#include "../NeuroSync.h"
#include <iostream>

int main() {
    std::cout << "NeuroSync test program started" << std::endl;
    
    // Initialize system
    neurosync_init();
    
    std::cout << "NeuroSync initialized" << std::endl;
    
    // Stop the system
    neurosync_stop();
    
    std::cout << "NeuroSync test program finished" << std::endl;
    
    return 0;
}