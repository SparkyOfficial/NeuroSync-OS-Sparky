#include "../NeuroSync.h"
#include <iostream>

int main() {
    std::cout << "Final test program started" << std::endl;
    
    // Initialize system
    neurosync_init();
    
    std::cout << "NeuroSync initialized" << std::endl;
    
    // Stop the system
    neurosync_stop();
    
    std::cout << "NeuroSync stopped" << std::endl;
    
    std::cout << "Final test program finished" << std::endl;
    
    return 0;
}