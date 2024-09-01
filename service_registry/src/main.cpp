#include "../include/ServiceRegistry.hpp"

int main() {
    TestTask::ServiceRegistry registry;
    
    // Example registration of services
    registry.registerService("CameraService", "tcp://localhost:5555");
    registry.registerService("StreamerService", "tcp://localhost:5557");
    
    // Example discovery
    std::string endpoint = registry.findService("StreamerService");
    if (!endpoint.empty()) {
        spdlog::info("StreamerService is available at {}", endpoint);
    } else {
        spdlog::info("StreamerService is not registered.");
    }
    return 0;
}
