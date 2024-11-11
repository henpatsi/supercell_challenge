#include "HealthBar.h"

HealthBar::HealthBar(int maxHealth)
{
	m_maxHealth = maxHealth;
	m_currentHealth = maxHealth;

	// m_background.setSize(sf::Vector2f(100, 10));
	// m_background.setFillColor(sf::Color::Black);
	// m_background.setOutlineColor(sf::Color::White);
	// m_background.setOutlineThickness(1);

	m_healthBar.setSize(sf::Vector2f(100, 10));
	m_healthBar.setFillColor(sf::Color::Red);
}

void HealthBar::updateHealth(int health)
{
	m_currentHealth = health;
	if (m_currentHealth < 0)
	{
		m_currentHealth = 0;
	}
	m_healthBar.setSize(sf::Vector2f(100 * ((float) m_currentHealth / m_maxHealth), 10));
}

void HealthBar::setPosition(sf::Vector2f position)
{
	// m_background.setPosition(position.x - m_background.getSize().x * 0.5f, position.y - m_background.getSize().y * 0.5f);
	m_healthBar.setPosition(position.x - m_healthBar.getSize().x * 0.5f, position.y - m_healthBar.getSize().y * 0.5f);
}

void HealthBar::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// target.draw(m_background, states);
	target.draw(m_healthBar, states);
}