#pragma once
#include "IDrawable.h"
#include "IUpdatable.h"

class MainMenu : public IDrawable, public IUpdatable {
private:
    int selectedOption;
    int totalOptions;

public:
    MainMenu();
    void Update() override;
    void Draw() const override;
    int GetSelectedOption() const;
    void Reset();
};