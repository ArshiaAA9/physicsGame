#pragma once

#include "CollisionDetection.h"
#include "ObjectHandler.h"
#include "Solver.h"
#include "Vector2.h"

namespace SE {

class PhysicsWorld {
public:
    CollisionDetection cD; // interface for
    ObjectHandler Handler; // public cause handles Objects

    /**
     *@param gridWidth simulations height
     *@param griHeight simulations width
     *@return
     * */
    PhysicsWorld(float gridWidth, float gridHeight)
        : cD(gridHeight, gridWidth, *this)
        , m_solver(*this)
        , Handler(*this) {}

    void step(float dt);

    void setGravity(Vector2 gravity);
    void invertGravity();

private:
    Solver m_solver;
    Vector2 m_gravity = Vector2(0, -0.81); // -0.81

    void dynamicsUpdate(float dt);
};
} // namespace SE
