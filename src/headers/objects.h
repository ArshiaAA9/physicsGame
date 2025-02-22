#pragma once

#include <iostream>
#include <vector>
#include "vector2.h"
#include "physics.h"
#include "Colliders.h"
#include "Transform.h"

struct Object;
struct rectObject;
struct CircleObject;

enum ObjectType {
    Rect;
    Circle;
    Tri;
}

//physical objects
struct Object {
    
    ObjectType Type; // type of the object

    float Mass;
    Vector2 Velocity; 
    Vector2 Force;

    Transform* Transform; // position and scale
    Collider* Collider; 


    Object(float x, float y, float mass)
        : Transform.Position(x, y)
        , Mass(mass){

            checkValidValues(Mass); // validate values
        }

    ~Object() = default;


    void applyForce(Vector2 force){


        Force += force;
    }

    // void updateVelocityAfterImpact(Object& cO){
    //     //1 obj Velocity 2 collided object cO = collidedObject
    //     Vector2 dV = Velocity - cO.Velocity;
    //     Vector2 dPos = Position - cO.Position;
    //     float massSum = Mass + cO.Mass;
    //     float dotDVdPos = dotProduct(dV, dPos);
    //     float distanceSquared = squaredLengthOf2Pos(Position, cO.Position);
    //     float scale = (2.0f / massSum) * (dotDVdPos / distanceSquared);
    //     Velocity = Velocity - (scale * cO.Mass) * dPos;         // Uses dPos
    //     cO.Velocity = cO.Velocity + (scale * Mass) * dPos;    
    // }



    void printProperties() const{

        std::cout << "Position: (" << this->Position.x << ", " << this->Position.y << ")" 
        << " Velocity: (" << this->Velocity.x << ", " << this->Velocity.y << ")" 
        << " Force: (" << this->Force.x << ", " << this->Force.y << ")\n";
    } 


private:

    void checkValidValues(float Mass){
        if (Mass <= 0.0f){
            throw std::invalid_argument("Mass must be positive value");
        }
    }

};


struct rectObject : public Object {
    
    int Height;
    int Width;


    rectObject(float x, float y, float mass, float Height, float Width)
        : Object(x, y, mass)
        , Height()
        , Width(Width){

            checkValidDimensions(Mass, Height, Width);
        }
    ~rectObject() = default;


private:
    // void checkCollisionRectwithRect(rectObject& collidedRect){
    //     float halfWidth1 = Width / 2, halfHeight1 = Height / 2;
    //     float halfWidth2 = collidedRect.Width / 2, halfHeight2 = collidedRect.Height / 2;
    //     float r1LeftX = Position.x - halfWidth1;
    //     float r1RightX = Position.x + halfWidth1;
    //     float r1TopY = Position.y - halfHeight1;
    //     float r1BottomY = Position.y + halfHeight1;
    //     float r2LeftX = collidedRect.Position.x - halfWidth2;
    //     float r2RightX = collidedRect.Position.x + halfWidth2;
    //     float r2TopY = collidedRect.Position.y - halfHeight2;
    //     float r2BottomY = collidedRect.Position.y + halfHeight2;
    //     if((r1LeftX < r2RightX) && (r1RightX > r2LeftX)&&
    //        (r1BottomY < r2TopY) && (r1TopY > r2BottomY)){
    //         updateVelocityAfterImpact(collidedRect);
    //     }
    // }
 

    void checkValidDimensions(float Mass, float Height, float Width) {
        // Helper function to check validity. used in constructors to avoid division by 0,0 Mass and negative friction
        if (Mass <= 0 || Height <= 0 || Width <= 0) {
            throw std::invalid_argument("Mass, Height, and Width must be positive int.");
        }
    }
};



struct CircleObject : public Object{
    
    float radius;


    CircleObject(float x, float y, float Mass, float radius) 
        : Object(x, y, Mass)
        , radius(radius) {
    }
    ~CircleObject() = default;

    
    
private:


};