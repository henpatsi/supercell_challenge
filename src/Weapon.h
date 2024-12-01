#pragma once

#include "Rectangle.h"
#include "Constants.h"

class Weapon : public Rectangle
{
public:
    Weapon();
    virtual ~Weapon() {}

    // Start
    void initialize();

    // Loop
    void update(float deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Setters
    void setActive(bool isActive, bool isVertical = false);
    void upgradeDamage(int amount);
    void upgradeAttackSize(float amount);

    // Getters
    bool isActive() { return m_isActive; }
    int getDamage() { return m_damage; }
    float getAttackSize() { return m_attackSize; }
    int getAttackID() { return m_attackID; }

private:
    bool m_isActive = false;

    // Stats
    int m_damage;
    float m_attackSize;
    float m_weaponHeight = 10.0f;
    float m_weaponWidth = 100.0f;

    // Timers
    float m_weaponActiveTime = 0.25f;
    float m_timer = 0.0f;

    uint m_attackID = 0;
};
