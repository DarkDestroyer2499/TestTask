#include "../include/TrackerService.hpp"

int main() {
    try {
        TestTask::TrackerService trackerService;
        trackerService.run();
    } catch (const std::exception& e) {
        spdlog::error("Exception: {}", e.what());
        return 1;
    }
    return 0;
}
