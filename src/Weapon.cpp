#include "Weapon.h"
#include "Constants.h"

Weapon::Weapon() : Rectangle(sf::Vector2f(0, 0))
{
    setPosition(sf::Vector2f(ScreenWidth * 0.5f, ScreenHeight * 0.5f));
    setOrigin(sf::Vector2f(0.0f, 0.0f));
    setColor(sf::Color::Blue);
}

void Weapon::setActive(bool isActive, bool isVertical)
{
    m_isActive = isActive;
    if (isActive)
    {
		if (!isVertical)
        	setSize(sf::Vector2f(m_weaponWidth, m_weaponHeight));
		else
			setSize(sf::Vector2f(m_weaponHeight, m_weaponWidth));
        m_timer = m_weaponActiveTime;

		m_attackID++;
    }
    else
    {
        setSize(sf::Vector2f(0.0f, 0.0f));
        m_timer = 0.0f;
    }
}

void Weapon::update(float deltaTime)
{
    if (m_isActive)
    {
        m_timer -= deltaTime;
        if (m_timer <= 0.0f)
        {
            setActive(false);
        }
    }
}

void Weapon::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RectangleShape graphicsRect(getSize());
    graphicsRect.setFillColor(getColor());
    graphicsRect.setPosition(getPosition());
    target.draw(graphicsRect);
}

// Upgrade

void Weapon::upgradeDamage(int amount)
{
	m_damage += amount;
}

void Weapon::upgradeAttackSize(float amount)
{
	m_attackSize += amount;
	m_weaponWidth *= m_attackSize;
	m_weaponHeight *= m_attackSize;
}