#pragma once
#include "../../../engine/src/headers/Physics.h"
#include "Sdl.h"

using namespace SE;

class Game {
public:
    Game(int windowWidth, int windowHeight)
        : m_world(windowWidth, windowHeight)
        , m_sdl(*this, windowWidth, windowHeight) {}

    int start();

    // used in Events class to create object dynamicly
    ObjectPtr createRect(float x, float y, float mass, float width, float height, SDL_Color color);

    void setMainObject(ObjectPtr object);
    ObjectPtr getMainObject();

    // event functions:
    void moveObject(ObjectPtr object, Vector2 amount);
    void moveObjectTo(ObjectPtr object, Vector2 position);
    void stopObject(ObjectPtr object);
    void deleteAllObjects();

private:
    void loopCount();

    Sdl m_sdl;
    PhysicsWorld m_world;
    ObjectPtr m_mainObject;
};
