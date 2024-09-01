#include "../include/StreamerService.hpp"

#define SHM_NAME "/shm_frame"
#define FRAME_WIDTH 640
#define FRAME_HEIGHT 480
#define FRAME_CHANNELS 3

namespace TestTask {
    StreamerService::StreamerService()
        : shm_fd(-1), shm_ptr(nullptr), window(nullptr), renderer(nullptr), texture(nullptr){
        // Initialize the logger
        logger = spdlog::stdout_color_mt("StreamerServiceLogger");

        // Set up shared memory
        shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
        if (shm_fd == -1) {
            logger->error("Error: Could not open shared memory.");
            throw std::runtime_error("Failed to open shared memory.");
        }

        shm_ptr = (uchar*)mmap(0, FRAME_WIDTH * FRAME_HEIGHT * FRAME_CHANNELS, PROT_READ, MAP_SHARED, shm_fd, 0);
        if (shm_ptr == MAP_FAILED) {
            logger->error("Error: Could not map shared memory.");
            throw std::runtime_error("Failed to map shared memory.");
        }

        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            logger->error("SDL_Init Error: {}", SDL_GetError());
            throw std::runtime_error("SDL_Init failed.");
        }

        // Create SDL window, renderer, and texture
        window = SDL_CreateWindow("Streamer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, FRAME_WIDTH, FRAME_HEIGHT, SDL_WINDOW_SHOWN);
        if (!window) {
            logger->error("SDL_CreateWindow Error: {}", SDL_GetError());
            throw std::runtime_error("Failed to create SDL window.");
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (!renderer) {
            logger->error("SDL_CreateRenderer Error: {}", SDL_GetError());
            throw std::runtime_error("Failed to create SDL renderer.");
        }

        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, FRAME_WIDTH, FRAME_HEIGHT);
        if (!texture) {
            logger->error("SDL_CreateTexture Error: {}", SDL_GetError());
            throw std::runtime_error("Failed to create SDL texture.");
        }
    }

    StreamerService::~StreamerService() {
        cleanup();
    }

    void StreamerService::run() {
        mIsRunning = true;

        while (mIsRunning) {
            // Read frame from shared memory
            cv::Mat frame(FRAME_HEIGHT, FRAME_WIDTH, CV_8UC3, shm_ptr);
            if (frame.empty()) {
                logger->error("Error: Failed to read frame from shared memory.");
                break;
            }

            // Display the frame
            cv::Mat frameRGB;
            cv::cvtColor(frame, frameRGB, cv::COLOR_BGR2RGB);
            SDL_UpdateTexture(texture, nullptr, frameRGB.data, frameRGB.step);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, nullptr, nullptr);
            SDL_RenderPresent(renderer);

            SDL_Delay(10);
        }
    }

    void StreamerService::stop() {
        mIsRunning = false;
    }

    void StreamerService::cleanup() {
        if (shm_ptr != MAP_FAILED) {
            munmap(shm_ptr, FRAME_WIDTH * FRAME_HEIGHT * FRAME_CHANNELS);
        }
        if (shm_fd != -1) {
            close(shm_fd);
        }
        if (texture) {
            SDL_DestroyTexture(texture);
        }
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
        SDL_Quit();
    }

} //!TestTask