#include "headers/Game.h"

#include <cmath>
#include <iostream>

#include "headers/Events.h"
#include "headers/Sdl.h"

using namespace SE;

int Game::start() {
    m_world.setGravity(Vector2(0, -30));
    float dt = 1.0f / 60.0f;
    float delay = 1000.0f / 60.0f;
    ObjectPtr rect1;
    ObjectPtr rect2;
    ObjectPtr rect3;
    ObjectPtr rect4;
    ObjectPtr circle;
    SDL_FColor color = {0, 255, 0, 255};
    SDL_FColor staticObjectColor = {0, 0, 255, 255};
    rect1 = createRect(100, 250.5, 1, 50, 100, color, 0);
    circle = createCircle(100, 150, 1, 50, color, 0);

    rect2 = createStaticRect(0, 250, 10, 450, staticObjectColor, 0);
    rect3 = createStaticRect(995, 250, 10, 450, staticObjectColor, 0);
    rect4 = createStaticRect(500, 0, 1000, 10, staticObjectColor, 0);

    setMainObject(rect1);
    m_world.cD.m_grid.updateCellDimensions();
    m_world.step(dt);

    // main loop
    while (m_sdl.event.loop()) {
        // loopCount();
        m_world.step(dt);
        m_sdl.renderer.update(m_world);
        SDL_Delay(delay);
    }
    return 0;
}

int Game::test() {
    // m_world.setGravity(Vector2(0, -0));
    // float dt = 1.0f / 60.0f;
    float delay = 1000.0f / 60.0f;

    while (m_sdl.event.loop()) {
        loopCount();
        m_sdl.renderer.update(m_world);
        SDL_Delay(delay);
    }
    return 0;
}

// test function
void Game::rotateObject(ObjectPtr object, float amount) {
    // std::cout << "position: " << object->transform.position << " angle: " <<
    // object->transform.angle << '\n'; object->transform.printVertices();
    object->transform.increaseAngle(amount);
    // std::cout << "angle: " << object->transform.angle << "\n";
    object->transform.transform();
    // object->transform.printVertices();
}

void Game::loopCount() {
    static int count = 1;
    std::cout << "loop count: " << count << std::endl;
    count++;
}

void Game::setMainObject(ObjectPtr object) { m_mainObject = object; }

ObjectPtr Game::getMainObject() { return m_mainObject; }

void Game::moveObject(ObjectPtr object, Vector2 amount) { object->applyForce(amount); }

void Game::moveObjectTo(ObjectPtr object, Vector2 position) { object->transform.moveTo(position); }

void Game::stopObject(ObjectPtr object) { object->setVelocity(Vector2(0, 0)); }

ObjectPtr Game::createRect(float x, float y, float mass, float width, float height,
                           SDL_FColor color, float angle) {
    ObjectPtr pObject = m_world.Handler.createRectObj(x, y, mass, width, height, angle);
    m_sdl.renderer.addRenderPair(pObject, color);
    return pObject;
}

ObjectPtr Game::createStaticRect(float x, float y, float width, float height, SDL_FColor color,
                                 float angle) {
    ObjectPtr pObject = m_world.Handler.createStaticRect(x, y, width, height, angle);
    m_sdl.renderer.addRenderPair(pObject, color);
    return pObject;
}

ObjectPtr Game::createCircle(float x, float y, float mass, float radius, SDL_FColor color,
                             float angle) {
    ObjectPtr pObject = m_world.Handler.createCircleObj(x, y, mass, radius, angle);
    m_sdl.renderer.addRenderPair(pObject, color);
    return pObject;
}

ObjectPtr Game::createStaticCircle(float x, float y, float radius, SDL_FColor color, float angle) {
    ObjectPtr pObject = m_world.Handler.createStaticCircle(x, y, radius, angle);
    m_sdl.renderer.addRenderPair(pObject, color);
    return pObject;
}

// NOTE:: can be optimized for performance
void Game::deleteAllObjects() {
    auto renderMap = m_sdl.renderer.getRenderMap(); // copy all objects
    std::vector<ObjectPtr> tempVector;              // NOTE: can play with this for performance
    for (const auto& [obj, color] : renderMap) {
        if (obj == m_mainObject) continue;
        tempVector.push_back(obj); // add them to temporarly vector
    }

    // Delete each object and remove from render map
    for (ObjectPtr obj : tempVector) {
        try {
            m_world.Handler.deleteObject(obj);    // Delete from the world
            m_sdl.renderer.deleteRenderPair(obj); // Remove from render map
        } catch (const std::exception& e) {
            std::cerr << "Error deleting object " << obj << ": " << e.what() << "\n";
        }
    }
}
