#include "../include/KeyboardInputService.hpp"

namespace TestTask
{
    KeyboardInputService::KeyboardInputService()
        : window(nullptr), context(1), socket(context, ZMQ_PUB) {
        // Initialize spdlog logger
        logger = spdlog::stdout_color_mt("KeyboardInputServiceLogger");

        // Initialize ZeroMQ socket
        socket.bind("tcp://*:5556");

        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            logger->error("SDL_Init Error: {}", SDL_GetError());
            throw std::runtime_error("SDL_Init failed");
        }

        // Create SDL window
        window = SDL_CreateWindow("Keyboard Input",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            640, 480, SDL_WINDOW_SHOWN);

        if (!window) {
            logger->error("SDL_CreateWindow Error: {}", SDL_GetError());
            SDL_Quit();
            throw std::runtime_error("SDL_CreateWindow failed");
        }
    }

    KeyboardInputService::~KeyboardInputService() {
        if (window) {
            SDL_DestroyWindow(window);
        }
        SDL_Quit();
    }

    void KeyboardInputService::run() {
        mIsRunning = true;
        while (mIsRunning) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                handleEvent(event);
            }
            SDL_Delay(10);  // Small delay to avoid hogging the CPU
        }
    }

    void KeyboardInputService::stop() {
        mIsRunning = false;
    }

    void KeyboardInputService::handleEvent(const SDL_Event& event) {
        if (event.type == SDL_QUIT) {
            stop();
        } else if (event.type == SDL_KEYDOWN) {
            zmq::message_t message;
            switch (event.key.keysym.sym) {
                case SDLK_1:
                    message = zmq::message_t("TRACK", 5);
                    logger->info("TRACK");
                    socket.send(message, zmq::send_flags::none);
                    break;
                case SDLK_0:
                    message = zmq::message_t("STOP", 4);
                    logger->info("STOP");
                    socket.send(message, zmq::send_flags::none);
                    break;
                case SDLK_ESCAPE:
                    message = zmq::message_t("QUIT", 4);
                    logger->info("QUIT");
                    socket.send(message, zmq::send_flags::none);
                    stop();
                    break;
                default:
                    logger->info("Other key pressed: {}", SDL_GetKeyName(event.key.keysym.sym));
                    break;
            }
        }
    }
} //!TestTask
