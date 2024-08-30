#include <opencv2/opencv.hpp>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#define SHM_NAME "/shm_frame"
#define FRAME_WIDTH 640
#define FRAME_HEIGHT 480

int main() {
    cv::VideoCapture cap(0);

    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, FRAME_WIDTH * FRAME_HEIGHT * 3);
    uchar* shm_ptr = (uchar*) mmap(0, FRAME_WIDTH * FRAME_HEIGHT * 3, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    while (true) {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty()) break;

        memcpy(shm_ptr, frame.data, FRAME_WIDTH * FRAME_HEIGHT * 3);
        usleep(30000);  // Simulate 30 FPS
    }

    cap.release();
    munmap(shm_ptr, FRAME_WIDTH * FRAME_HEIGHT * 3);
    close(shm_fd);
    shm_unlink(SHM_NAME);

    return 0;
}
