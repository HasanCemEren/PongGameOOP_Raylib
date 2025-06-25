#pragma once
#include "IDrawable.h"
#include "IUpdatable.h"

class Entity : public IDrawable, public IUpdatable {
protected:
    float x, y;
public:
    virtual ~Entity() = default; //It's virtual because the inherited objects are also need a destructor.
    float GetX() const { return x; }
    float GetY() const { return y; }
};