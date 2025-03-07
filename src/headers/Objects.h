#pragma once

#include <iostream>
#include <vector>

#include "Transform.h"
#include "Vector2.h"

struct Object;
struct RectObject;
struct CircleObject;

struct Object {
    enum ObjectType { CIRCLE, RECT };

    float mass;
    Vector2 velocity;
    Vector2 force;

    ObjectType type;
    Transform transform; // position and scale

    // constructor:
    Object(float x, float y, float mass, ObjectType type)
        : transform(x, y)
        , mass(mass)
        , type(type) {
        checkValidValues(mass);
    }

    virtual ~Object() = default;

    virtual Vector2 getDimensions() const = 0;

    virtual void printProperties() const;

    void applyForce(Vector2 force);

private:
    void checkValidValues(float mass) const;
};

struct RectObject : public Object {

    int height;
    int width;

    // constructor:
    RectObject(float x, float y, float mass, float height, float width)
        : Object(x, y, mass, RECT)
        , height(height)
        , width(width) {
        checkValidDimensions(mass, height, width);
    }
    ~RectObject() = default;

    Vector2 getDimensions() const override;

    void printProperties() const override;

private:
    void checkValidDimensions(float mass, float height, float width) const;
};

struct CircleObject : public Object {
    float radius;

    // constructor:
    CircleObject(float x, float y, float mass, float radius)
        : Object(x, y, mass, CIRCLE)
        , radius(radius) {}
    ~CircleObject() = default;

    Vector2 getDimensions() const override;

    void printProperties() const override;

private:
    void checkValidDimensions(float mass, float radius) const;
};
