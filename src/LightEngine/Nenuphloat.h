#pragma once
#include "Ally.h"

class Nenuphloat : public Ally
{
    float mDuration = 5.f;
    float mProgress = 0.f;

    sf::Vector2f mDefaultSize = {0.f, 0.f};
    sf::Vector2f mGrownSize = { 0.f, 0.f };

    sf::Vector2f mPosition;

public:
    void OnInitialize() override;
    void OnUpdate() override;
    void FixedUpdate(float dt) override;
    void OnCollision(Entity* collidedWith) override;
    void LoadAnimation() override;

private:
    bool CheckClosed();
    void Grow();
    void Retract();
    bool grown = false;
};