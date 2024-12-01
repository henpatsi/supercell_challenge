#pragma once

#include <SFML/Graphics.hpp>

class HealthBar
{
public:
    HealthBar(int maxHealth, float scale = 1.0f);

    // Loop
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    // Setters
    void updateHealth(int health);
    void setPosition(sf::Vector2f position);

private:
    // References
    // sf::RectangleShape m_background;
    sf::RectangleShape m_healthBar;

    // Stats
    int m_currentHealth;
    int m_maxHealth;
    float m_scale;
};