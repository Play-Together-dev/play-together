#include <thread>
#include <mutex>
#include "../include/Game/Game.h"
#include "../include/Utils/GameConsole.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *args[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return 1;
    }

    /*
    window = SDL_CreateWindow(
            "Play Together",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_FULLSCREEN
    );*/

    window = SDL_CreateWindow("Play Together", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Player initialPlayer(50, 50, 1, 2, 20, 30);

    Player character1(100, 50, 1, 2, 20, 30);
    Player character2(150, 50, 1, 2, 20, 30);
    Player character3(200, 50, 1, 2, 20, 30);

    Game game(window, renderer, initialPlayer);
    GameConsole console(&game);

    game.loadPolygonsFromMap("diversity");

    //game.addCharacter(character1);
    //game.addCharacter(character2);
    game.addCharacter(character3);

    game.removeCharacter(character3);

    game.initializeCameraPosition();

    game.run();

    // Launch the game console in a separate thread
    std::jthread consoleThread(&GameConsole::Run, &console);

    // Join the console thread
    consoleThread.join();

    return 0;
}
