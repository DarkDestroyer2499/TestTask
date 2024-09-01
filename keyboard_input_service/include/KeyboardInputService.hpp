#pragma once

#include <SDL2/SDL.h>
#include <zmq.hpp>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "../../include_common/IService.hpp"

namespace TestTask 
{
    class KeyboardInputService : public IService {
    public:
        KeyboardInputService();
        ~KeyboardInputService();

        void run() override;
        void stop() override;

    private:
        void handleEvent(const SDL_Event& event);
  
        SDL_Window* window;
        zmq::context_t context;
        zmq::socket_t socket;
        std::shared_ptr<spdlog::logger> logger;
    };

} //!TestTask