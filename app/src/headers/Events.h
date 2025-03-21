#pragma once

#include <SDL2/SDL_events.h>

#include "../../../engine/src/headers/Types.h"

class Game;
class PhysicsWorld;
class Sdl;

class Events {
public:
    Events(Sdl& sdl, Game& game)
        : m_sdl(sdl)
        , m_game(game) {}

    // main event loop with PollEvent()
    bool loop(ObjectPtr obj);

    SDL_Event& getEventVar();

private:
    // these functions are used in loop inside the switch cases
    void keydownEvents(ObjectPtr obj);
    void mouseButtonUpEvents();

    // game related functions:
    void createRectOnMousePos(int mx, int my, float m, float width, float height, SDL_Color color = {255, 0, 0, 1});
    void deleteAllObjects();

    Game& m_game;
    SDL_Event m_sdlEvent;
    Sdl& m_sdl;
};
