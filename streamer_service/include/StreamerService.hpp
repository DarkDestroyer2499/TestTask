#pragma once

#include <opencv2/opencv.hpp>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <zmq.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "../../include_common/IService.hpp"

namespace TestTask
{
    class StreamerService : public IService
    {
    public:
        StreamerService();
        ~StreamerService();

        void run() override;
        void stop() override;

    private:
        void cleanup();

    private:
        int shm_fd;
        uchar* shm_ptr;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        std::shared_ptr<spdlog::logger> logger;
    };
} //!TestTask
