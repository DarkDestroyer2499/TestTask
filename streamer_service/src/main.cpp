#include <opencv2/opencv.hpp>
#include <SDL2/SDL.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#define SHM_NAME "/shm_frame"
#define FRAME_WIDTH 640
#define FRAME_HEIGHT 480

int main() {
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    uchar* shm_ptr = (uchar*) mmap(0, FRAME_WIDTH * FRAME_HEIGHT * 3, PROT_READ, MAP_SHARED, shm_fd, 0);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Streamer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, FRAME_WIDTH, FRAME_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

    while (true) {
        cv::Mat frame(FRAME_HEIGHT, FRAME_WIDTH, CV_8UC3, shm_ptr);

        if (frame.empty()) break;

        cv::Mat frameRGB;
        cv::cvtColor(frame, frameRGB, cv::COLOR_BGR2RGB);
        SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
            frameRGB.data, frameRGB.cols, frameRGB.rows, 24, frameRGB.step,
            0x000000ff, 0x0000ff00, 0x00ff0000, 0
        );

        SDL_BlitSurface(surface, NULL, screenSurface, NULL);
        SDL_UpdateWindowSurface(window);
        SDL_FreeSurface(surface);

        usleep(30000);  // Simulate 30 FPS
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    munmap(shm_ptr, FRAME_WIDTH * FRAME_HEIGHT * 3);
    close(shm_fd);

    return 0;
}
