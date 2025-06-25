#pragma once
#include "Entity.h"
#include <raylib.h>

enum class PowerUpType {
    SHOE,     // Ball speeds up
    JACKET,   // Paddle get height
    DRESS,    // Paddle speeds up
    NECKLACE, // Ball grows
    HAT,      // Shield
    BAG       // Double point
};

class PowerUp : public Entity {
private:
    PowerUpType type;
    float rotation;
    float spawnTime;
    bool active;
    float size;

public:
    PowerUp(float xPos, float yPos, PowerUpType powerType);
    void Update() override;
    void Draw() const override;
    bool IsActive() const;
    void Deactivate();
    PowerUpType GetType() const;
    bool IsExpired() const;
    Rectangle GetBounds() const;
};

