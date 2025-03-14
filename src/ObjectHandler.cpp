#include "headers/ObjectHandler.h"

#include <algorithm>
#include <memory>

void ObjectHandler::addObject(std::unique_ptr<Object>&& object) { m_objects.push_back(std::move(object)); }

void ObjectHandler::deleteObject(Object* object) {
    if (!object) return;
    // using a lambda to get unique_ptr's raw pointer to compare it to object
    auto itr = std::find_if(m_objects.begin(), m_objects.end(), [object](const std::unique_ptr<Object>& ptr) {
        return ptr.get() == object;
    });
    if (itr == m_objects.end()) return;
    m_objects.erase(itr);
}

/**@return returns pointer all objects in the world**/
const std::vector<std::unique_ptr<Object>>& ObjectHandler::getObjects() const { return m_objects; }

/**
 * @brief Creates a rectObject and adds it to the world
 * @brief returning a pointer raw pointer so user can interact with it
 *
 * This function creates a new `RectObject` with the specified position, mass, width, and height.
 * The newly created object is then added to the world managed by the `ObjectHandler`.
 *
 * @param x The x-coordinate of the object's position.
 * @param y The y-coordinate of the object's position.
 * @param mass The mass of the object.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @return A pointer to the newly created `RectObject`.
 *
 */
Object* ObjectHandler::createRectObj(float x, float y, float mass, float width, float height) {
    std::unique_ptr<Object> rectObject = std::make_unique<RectObject>(x, y, mass, width, height);
    Object* ptr = rectObject.get();
    addObject(std::move(rectObject));
    return ptr;
}

/**
 * @brief Creates a circular object and adds it to the world.
 *
 * This function creates a new `CircleObject` with the specified position, mass, and radius.
 * The newly created object is then added to the world managed by the `ObjectHandler`.
 *
 * @param x The x-coordinate of the object's position.
 * @param y The y-coordinate of the object's position.
 * @param mass The mass of the object.
 * @param radius The radius of the circle.
 * @return A pointer to the newly created `CircleObject`.
 *
 */
Object* ObjectHandler::createCircleObj(float x, float y, float mass, float radius) {
    std::unique_ptr<Object> circleObject = std::make_unique<CircleObject>(x, y, mass, radius);
    Object* ptr = circleObject.get();
    addObject(std::move(circleObject));
    return ptr;
}
