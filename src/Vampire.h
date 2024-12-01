#pragma once

#include "Rectangle.h"
#include "HealthBar.h"
#include <SFML/Audio.hpp>

class Game;

class Vampire : public Rectangle
{
public:
    Vampire(Game* game, sf::Vector2f position, int level);
    virtual ~Vampire() {}

    // Loop
    void update(float deltaTime);
    void move(float deltaTime);
    void takeDamage(int damage, int attackID);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Getters
    bool isKilled() { return m_isKilled; }

private:
    // References
    Game* m_pGame;
    HealthBar m_healthBar;

    // Stats
    bool m_isKilled = false;
    int m_level;
    int m_health;
    int m_damage;
    float m_moveSpeed;

    // Timers
    float m_stopDuration = 0.2f;
    float m_stopTimer = 0.0f;

    int m_lastAttackID = 0;

    // Audio
    sf::Sound m_sound;
};
