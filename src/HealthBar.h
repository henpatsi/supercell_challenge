#pragma once

#include <SFML/Graphics.hpp>

class HealthBar
{
public:
	HealthBar(int maxHealth, float scale = 1.0f);
	void updateHealth(int health);
	void setPosition(sf::Vector2f position);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	// sf::RectangleShape m_background;
	sf::RectangleShape m_healthBar;

	int m_currentHealth;
	int m_maxHealth;

	float m_scale;
};