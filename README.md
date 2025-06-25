# OOP Pong Game 🏓

So I decided to remake the classic Pong game, but this time I wanted to really focus on object-oriented programming principles. What started as a simple paddle-and-ball game turned into something way cooler with fashion-themed power-ups and a solid class architecture that I'm actually pretty proud of.

## What I Built

- Classic Pong gameplay (obviously) with player vs CPU
- 6 different fashion-themed power-ups because why not make it stylish?
- Built with C++ and Raylib - runs at 144 FPS and feels super smooth
- Proper menu system and game states
- Shield mechanics for some defensive strategy

## The OOP Structure (This is where it gets interesting)

I spent a lot of time thinking about how to structure this properly. Coming from spaghetti code in my earlier projects, I really wanted to get the architecture right this time.

### Why I Used Interfaces

First thing I did was create two simple interfaces:

```cpp
class IDrawable {
public:
    virtual void Draw() const = 0;
};

class IUpdatable {
public:
    virtual void Update() = 0;
};
```

I know it seems basic, but this was a game-changer. Instead of having giant classes that do everything, now each class only implements what it actually needs. My Ball class needs both drawing and updating, but my ScoreBoard only needs drawing. Clean and simple.

# Polymorphism in Action 🔄

One of the coolest improvements I made was implementing true polymorphism in the main game loop. Instead of calling each object's methods individually, I now use polymorphic collections:

## Before (Repetitive Code):
```cpp
void Game::Run() {
    // Manual updates - not polymorphic
    ball.Update();
    player.Update();
    cpu.Update();
    
    // Manual drawing - not polymorphic
    ball.Draw();
    player.Draw();
    cpu.Draw();
    scoreboard.Draw();
}
```

## After (Polymorphic Magic):
```cpp
class Game {
private:
    std::vector<Entity*> entities;
    std::vector<IDrawable*> drawables;
    
public:
    Game() {
        // Initialize polymorphic collections
        entities = {&ball, &player, &cpu};
    }
    
    void Run() {
        // Polymorphic updates - each object calls its own Update()
        for (auto* entity : entities) {
            entity->Update(); // Ball::Update(), PlayerPaddle::Update(), CpuPaddle::Update()
        }
        
        // Polymorphic drawing - each object calls its own Draw()  
        for (auto* drawable : drawables) {
           entity->Draw(); // Different Draw() methods called automatically
        }
    }
};
```

## Why This is Awesome:

**🎯 Single Responsibility**: The game loop doesn't need to know HOW each object updates or draws itself
- `Ball::Update()` handles physics and collision detection
- `PlayerPaddle::Update()` handles keyboard input
- `CpuPaddle::Update()` handles AI behavior
- Each calls the RIGHT method automatically!

**🔧 Easy to Extend**: Want to add a new game object?
```cpp
class PowerUp : public Entity {
    void Update() override { /* power-up logic */ }
    void Draw() const override { /* power-up rendering */ }
};

// Just add it to the collection - no code changes needed!
entities.push_back(&powerUp);
drawables.push_back(&powerUp);
```

**🧹 Cleaner Code**: The game loop went from knowing about every specific object to being completely generic. It just says "update everything that can be updated" and "draw everything that can be drawn."

**⚡ Runtime Flexibility**: The same loop can handle completely different object types. A `Ball` bounces around, a `PlayerPaddle` responds to input, a `CpuPaddle` follows the ball - but the game loop treats them all the same way.

This is polymorphism working exactly as intended: **same interface, different behavior**. The game loop calls `Update()` on everything, but each object does something completely different when that method is called.

### The Entity Base Class

Then I created this Entity class that basically became the parent of all my game objects:

```cpp
class Entity : public IDrawable, public IUpdatable {
protected:
    float x, y;  // Everyone needs a position
public:
    float GetX() const { return x; }
    float GetY() const { return y; }
};
```

This was perfect because every game object needs a position, and most need to be drawn and updated. Now all my game objects inherit from Entity and get this functionality for free.

### How I Handled the Paddles

This is probably my favorite part of the design. I have a base Paddle class, then PlayerPaddle and CpuPaddle that inherit from it:

```cpp
class Paddle : public Entity {
    // All the common paddle stuff like size, power-ups, drawing
};

class PlayerPaddle : public Paddle {
    void Update() override {
        // Keyboard controls
    }
};

class CpuPaddle : public Paddle {
    void Update() override {
        // AI behavior
    }
};
```

The cool thing here is that both paddles look exactly the same and have the same power-up system, but they move completely differently. The PlayerPaddle responds to arrow keys, while the CpuPaddle follows the ball with some basic AI. Same interface, different behavior - that's polymorphism working exactly how it should.

### The Power-Up System (My favorite feature)

I wanted power-ups, but I also wanted them to be fun and memorable. So instead of boring "speed boost" and "bigger paddle", I went with a fashion theme:

- 👠 **Shoe**: Makes the ball faster (because fast fashion, get it?)
- 🧥 **Jacket**: Makes your paddle taller 
- 👗 **Dress**: Makes your paddle move faster
- 💎 **Necklace**: Makes the ball bigger and easier to hit
- 🎩 **Hat**: Gives you a shield that blocks one hit
- 👜 **Bag**: Doubles your points (because shopping is expensive)

Each power-up is a separate object with its own drawing logic and effects. They spawn randomly, rotate and glow to catch your attention, and disappear after 15 seconds if you don't grab them.

## The Main Game Class

Instead of inheriting from something, my Game class uses composition - it contains all the other objects:

```cpp
class Game {
private:
    Ball ball;
    PlayerPaddle player;
    CpuPaddle cpu;
    ScoreBoard scoreboard;
    MainMenu mainMenu;
    std::vector<PowerUp> powerUps;
};
```

This felt way more natural than trying to make Game inherit from something. The game HAS a ball, it HAS paddles, it HAS power-ups. It doesn't need to BE any of those things.

## What I Learned

### Composition vs Inheritance
I used to try to inherit from everything. Now I realize composition is often better. My Game class doesn't inherit from anything - it just contains the objects it needs to manage.

### Keep Interfaces Small
Those two simple interfaces (IDrawable and IUpdatable) do so much heavy lifting. Way better than one giant interface that forces classes to implement methods they don't need.

### State Management
I used an enum for game states instead of boolean flags everywhere:

```cpp
enum class GameStateEnum {
    MAIN_MENU, PLAYING, PAUSED, GAME_OVER
};
```

This made the code so much cleaner and easier to debug.

### Global State Done Right
Instead of singleton patterns or global variables everywhere, I used a simple namespace for the score:

```cpp
namespace GameState {
    extern int playerScore;
    extern int cpuScore;
}
```

Simple, clean, and accessible when needed.

## The Fun Stuff

### Collision Detection
I spent way too much time getting the collision detection just right. The ball needs to bounce off paddles at different angles depending on where it hits, and power-ups need to detect when the ball touches them.

### Visual Effects
When you have a power-up active, your paddle glows and shows a timer bar. The ball changes color based on its current state. Power-ups rotate and pulse. These little details make the game feel alive.

### AI Behavior
The CPU paddle isn't just following the ball directly - that would be too hard to beat. It has some intentional imperfection that makes it challenging but fair.

## How to Build and Run

You'll need Raylib installed, then just:

```bash
g++ -o pong *.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

Use arrow keys to move, Enter to navigate menus, and Escape to go back.

## What's Next?

The architecture makes it super easy to add new stuff:
- Want a new power-up? Just add it to the enum and implement the drawing logic
- Want a different paddle behavior? Inherit from Paddle and override Update()
- Want particle effects? Create a new Entity subclass

I'm thinking about adding sound effects, maybe some particle systems, or even multiplayer. The OOP structure means any of these would be pretty straightforward to add.

---

This was my first real attempt at proper OOP design in a game, and I'm pretty happy with how it turned out. The code is clean, extensible, and actually fun to work with. If you're learning OOP, maybe this can give you some ideas for your own projects!
