#include "../include/CameraService.hpp"

namespace TestTask
{
    CameraService::CameraService()
    : shm_fd(-1), shm_ptr(nullptr) {
        // Set up logger
        logger = spdlog::stdout_color_mt("CameraServiceLogger");

        // Set up shared memory
        shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
        if (shm_fd == -1) {
            logger->error("Error: Could not create shared memory.");
            throw std::runtime_error("Could not create shared memory.");
        }
        
        if (ftruncate(shm_fd, FRAME_WIDTH * FRAME_HEIGHT * FRAME_CHANNELS) == -1) {
            logger->error("Error: Could not set shared memory size.");
            throw std::runtime_error("Could not set shared memory size.");
        }

        shm_ptr = (uchar*)mmap(0, FRAME_WIDTH * FRAME_HEIGHT * FRAME_CHANNELS, PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (shm_ptr == MAP_FAILED) {
            logger->error("Error: Could not map shared memory.");
            throw std::runtime_error("Could not map shared memory.");
        }

        // Set up camera
        if (!cap.open(0)) {
            logger->error("Error: Could not open the camera.");
            throw std::runtime_error("Could not open the camera.");
        }
    }

    CameraService::~CameraService() {
        // Clean up shared memory
        if (shm_ptr != MAP_FAILED) {
            munmap(shm_ptr, FRAME_WIDTH * FRAME_HEIGHT * FRAME_CHANNELS);
        }
        if (shm_fd != -1) {
            close(shm_fd);
            shm_unlink(SHM_NAME);
        }

        // Release camera
        cap.release();
    }

    void CameraService::run()
    {
        mIsRunning = true;
        while (mIsRunning) {
            cv::Mat frame;
            cap >> frame;
            if (frame.empty()) {
                logger->error("Error: Failed to capture frame.");
                break;
            }

            // Write frame to shared memory
            memcpy(shm_ptr, frame.data, FRAME_WIDTH * FRAME_HEIGHT * FRAME_CHANNELS);

            // Small delay to avoid hogging CPU
            usleep(10000);
        }
    }

    void CameraService::stop()
    {
        mIsRunning = false;
    }
} //!TestTask
