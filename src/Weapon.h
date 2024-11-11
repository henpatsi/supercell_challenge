#pragma once

#include "Rectangle.h"

class Weapon : public Rectangle
{
public:
    Weapon();
    virtual ~Weapon() {}

    void setActive(bool isActive, bool isVertical = false);
    void update(float deltaTime);
    bool isActive() { return m_isActive; }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void upgradeDamage(int amount);
	void upgradeAttackSize(float amount);

	float getDamage() { return m_damage; }
	int getAttackID() { return m_attackID; }

private:
    bool m_isActive = false;
    float m_timer = 0.0f;

	int m_damage = 10;
	float m_attackSize = 1.0f;

	float m_weaponHeight = 10.0f;
	float m_weaponWidth = 100.0f;
	float m_weaponActiveTime = 0.25f;

	uint m_attackID = 0;
};