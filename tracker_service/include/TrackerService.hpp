#pragma once

#include <opencv2/opencv.hpp>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <zmq.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "../../include_common/IService.hpp"

#define SHM_NAME "/shm_frame"
#define FRAME_WIDTH 640
#define FRAME_HEIGHT 480
#define FRAME_CHANNELS 3

namespace TestTask
{
    class TrackerService : public IService {
    public:
        TrackerService();
        ~TrackerService();

        void run() override;
        void stop() override;

    private:
        void processTracking();
        void cleanup();
        
    private:
        zmq::context_t context;
        zmq::socket_t socket;
        std::shared_ptr<spdlog::logger> logger;
        int shm_fd;
        uchar* shm_ptr;
        bool tracking;
        cv::Mat prevGray;
        std::vector<cv::Point2f> prevPoints;
    };
} //!TestTask