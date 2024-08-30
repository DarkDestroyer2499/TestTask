#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

class ServiceRegistry {
private:
    std::unordered_map<std::string, std::string> registry;

public:
    void registerService(const std::string& serviceName, const std::string& endpoint) {
        registry[serviceName] = endpoint;
        std::cout << "Service " << serviceName << " registered at " << endpoint << std::endl;
    }

    std::string findService(const std::string& serviceName) {
        if (registry.find(serviceName) != registry.end()) {
            return registry[serviceName];
        } else {
            return "";
        }
    }
};

int main() {
    ServiceRegistry registry;
    
    // Example registration of services
    registry.registerService("CameraService", "tcp://localhost:5555");
    registry.registerService("StreamerService", "tcp://localhost:5557");
    
    // Example discovery
    std::string endpoint = registry.findService("StreamerService");
    if (!endpoint.empty()) {
        std::cout << "StreamerService is available at " << endpoint << std::endl;
    } else {
        std::cout << "StreamerService is not registered." << std::endl;
    }

    return 0;
}
