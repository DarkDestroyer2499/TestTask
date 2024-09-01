#include "../include/TrackerService.hpp"

namespace TestTask
{
    TrackerService::TrackerService()
        : context(1), socket(context, ZMQ_SUB), shm_fd(-1), shm_ptr(nullptr), tracking(false) {
        // Initialize the logger
        logger = spdlog::stdout_color_mt("TrackerServiceLogger");

        // Set up ZeroMQ
        socket.connect("tcp://localhost:5556");
        socket.set(zmq::sockopt::subscribe, "");

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
    }

    TrackerService::~TrackerService() {
        cleanup();
    }

    void TrackerService::stop() {
        mIsRunning = false;
    }

    void TrackerService::run() {
        mIsRunning = true;
        while (mIsRunning) {
            zmq::message_t message;
            if (socket.recv(message, zmq::recv_flags::dontwait)) {
                std::string command(static_cast<char*>(message.data()), message.size());
                logger->info("Received command: {}", command);

                if (command == "TRACK") {
                    tracking = true;
                    logger->info("Tracking started.");
                } else if (command == "STOP") {
                    tracking = false;
                    logger->info("Tracking stopped.");
                } else if (command == "QUIT") {
                    logger->info("Tracker service quitting.");
                    break;
                }
            }

            if (tracking) {
                processTracking();
            }

            usleep(10000);  // Small delay to avoid hogging CPU
        }
    }

    void TrackerService::processTracking() {
        // Read frame from shared memory
        cv::Mat frame(FRAME_HEIGHT, FRAME_WIDTH, CV_8UC3, shm_ptr);
        if (frame.empty()) {
            logger->error("Error: Failed to read frame from shared memory.");
            return;
        }

        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        if (prevPoints.empty()) {
            cv::goodFeaturesToTrack(gray, prevPoints, 100, 0.3, 7, cv::Mat(), 7, false, 0.04);
            prevGray = gray.clone();
        } else {
            std::vector<cv::Point2f> nextPoints;
            std::vector<uchar> status;
            std::vector<float> err;

            cv::calcOpticalFlowPyrLK(prevGray, gray, prevPoints, nextPoints, status, err);

            std::vector<cv::Point2f> goodNew, goodOld;
            for (size_t i = 0; i < status.size(); i++) {
                if (status[i]) {
                    goodNew.push_back(nextPoints[i]);
                    goodOld.push_back(prevPoints[i]);
                }
            }

            prevGray = gray.clone();
            prevPoints = goodNew;

            // Process the tracked points here
            logger->info("Tracked {} points.", goodNew.size());
        }
    }

    void TrackerService::cleanup() {
        if (shm_ptr != MAP_FAILED) {
            munmap(shm_ptr, FRAME_WIDTH * FRAME_HEIGHT * FRAME_CHANNELS);
        }
        if (shm_fd != -1) {
            close(shm_fd);
        }
    }
} //!TestTask
