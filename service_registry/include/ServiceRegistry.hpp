#pragma once

#include <unordered_map>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace TestTask
{
    class ServiceRegistry {
    public:
        ServiceRegistry();
        void registerService(const std::string& serviceName, const std::string& endpoint);
        std::string findService(const std::string& serviceName);

    private:
        std::unordered_map<std::string, std::string> registry;
        std::shared_ptr<spdlog::logger> logger;
    };

} //!TestTask
