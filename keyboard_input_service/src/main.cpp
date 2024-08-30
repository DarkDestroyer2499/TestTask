#include <SDL2/SDL.h>
#include <zmq.hpp>
#include <string>
#include <iostream>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:5556");

    SDL_Init(SDL_INIT_VIDEO);

    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                zmq::message_t message;
                if (event.key.keysym.sym == SDLK_1) {
                    message = zmq::message_t("TRACK", 5);
                } else if (event.key.keysym.sym == SDLK_0) {
                    message = zmq::message_t("STOP", 4);
                } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    message = zmq::message_t("QUIT", 4);
                    socket.send(message);
                    SDL_Quit();
                    return 0;
                }
                socket.send(message);
            }
        }
    }

    SDL_Quit();
    return 0;
}
