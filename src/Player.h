#pragma once

#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <memory>

#include "Rectangle.h"
#include "Weapon.h"
#include "InputHandler.h"
#include "Constants.h"
#include "Game.h"
#include "HealthBar.h"

#define SPRITE_SCALE 3.5f

struct InputData;

class Game;
class Weapon;

enum eDirection
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

class Player : public Rectangle
{
public:
    Player(Game* pGame);
    virtual ~Player() {}

    // Start
    bool initialise();

    // Loop
    void update(float deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Functionality
    void move(InputData inputData, float deltaTime);
    void attack();
    void setWeaponPosition();
    void takeDamage(int damage);

    // Upgrades
    void upgradeSpeed(float amount);
    void upgradeDamage(float amount);
    void upgradeAttackSize(float amount);

    // Getters
    Weapon* getWeapon() { return m_pWeapon.get(); }
    HealthBar* getHealthBar() { return m_pHealthBar.get(); }
    int getMoveSpeed() const { return m_moveSpeed; }
    int getHealth() const { return m_health; }
    bool isDead() const { return m_isDead; }

private:
    // References
    Game* m_pGame;
    std::unique_ptr<Weapon> m_pWeapon;
    std::unique_ptr<HealthBar> m_pHealthBar;

    // Stats
    bool m_isDead = false;
    int m_health;
    int m_moveSpeed;
    eDirection m_direction = LEFT;

    // Timers
    float m_damageCooldown;
    float m_damageTimer = 0.0f;
    float m_attackCooldown;
    float m_attackTimer = 0.0f;

    // Audio
    sf::Sound m_sound;
};
