#include <opencv2/opencv.hpp>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#define SHM_NAME "/shm_tracking"
#define FRAME_WIDTH 640
#define FRAME_HEIGHT 480

int main() {
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, FRAME_WIDTH * FRAME_HEIGHT * 3);
    uchar* shm_ptr = (uchar*) mmap(0, FRAME_WIDTH * FRAME_HEIGHT * 3, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    cv::Mat prevGray;
    std::vector<cv::Point2f> prevPoints;

    while (true) {
        cv::Mat frame(FRAME_HEIGHT, FRAME_WIDTH, CV_8UC3, shm_ptr);
        if (frame.empty()) break;

        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        if (prevPoints.empty()) {
            cv::goodFeaturesToTrack(gray, prevPoints, 100, 0.3, 7, cv::noArray(), 7);
        } else {
            std::vector<cv::Point2f> nextPoints;
            std::vector<uchar> status;
            cv::calcOpticalFlowPyrLK(prevGray, gray, prevPoints, nextPoints, status, cv::noArray(), cv::Size(15, 15), 2);

            for (size_t i = 0; i < status.size(); i++) {
                if (!status[i]) {
                    nextPoints.erase(nextPoints.begin() + i);
                }
            }

            prevPoints = nextPoints;
        }

        prevGray = gray.clone();

        memcpy(shm_ptr, frame.data, FRAME_WIDTH * FRAME_HEIGHT * 3);

        usleep(30000);  // Simulate 30 FPS
    }

    munmap(shm_ptr, FRAME_WIDTH * FRAME_HEIGHT * 3);
    close(shm_fd);
    shm_unlink(SHM_NAME);

    return 0;
}
