#include "../include/ServiceRegistry.hpp"

namespace TestTask
{
    ServiceRegistry::ServiceRegistry()
    {
        logger = spdlog::stdout_color_mt("ServiceRegistry");
    }

    void ServiceRegistry::registerService(const std::string& serviceName, const std::string& endpoint)
    {
        registry[serviceName] = endpoint;
        logger->info("Service {} registered at {}", serviceName, endpoint);
    }

    std::string ServiceRegistry::findService(const std::string& serviceName)
    {
        if (registry.find(serviceName) != registry.end()) {
            return registry[serviceName];
        } else {
            return "";
        }
    }
} //!TestTask
