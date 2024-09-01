#include "../include/StreamerService.hpp"

int main() {
    try {
        TestTask::StreamerService streamer;
        streamer.run();
    } catch (const std::exception& e) {
        spdlog::error("Exception: {}", e.what());
        return 1;
    }
    return 0;
}
