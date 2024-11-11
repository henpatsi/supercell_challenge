#include "Vampire.h"
#include "Constants.h"
#include "Game.h"
#include "Weapon.h"
#include "Player.h"
#include "MathUtils.h"

#include <iostream>

Vampire::Vampire(Game* game, sf::Vector2f position, int level) :
    Rectangle(sf::Vector2f(VampireWidth * level, VampireHeight * level)),
    m_pGame(game)
{
    setPosition(position);
    setOrigin(sf::Vector2f(0.0f, 0.0f));
    m_isKilled = false;

    m_sprite.setTexture(*m_pGame->getVampireTexture());
    m_sprite.setScale(2.0f, 2.0f); // Scale the sprite to match the rectangle size
	m_sprite.scale(level, level);

	m_health = VampireBaseHealth * level;
	m_damage = VampireBaseDamage * level;
	m_moveSpeed = VampireBaseSpeed + (level * 10);
	m_level = level;
}

void Vampire::update(float deltaTime)
{
    if (m_isKilled)
        return;
    
    Player* pPlayer = m_pGame->getPlayer();
	Weapon* pWeapon = pPlayer->getWeapon();

    if (collidesWith(pWeapon) && pWeapon->isActive())
    {
        takeDamage(pWeapon->getDamage(), pWeapon->getAttackID());
		if (m_isKilled)
			m_pGame->onVampireKilled(m_level);
        return;
    }

    if (collidesWith(pPlayer))
	{
        pPlayer->takeDamage(m_damage);
		m_stopTimer = m_stopDuration;
	}

	if (m_stopTimer > 0.0f)
		m_stopTimer -= deltaTime;
	else
		move(deltaTime);
}

void Vampire::move(float deltaTime)
{
	sf::Vector2f playerCenter = m_pGame->getPlayer()->getCenter();
    sf::Vector2f direction = VecNormalized(playerCenter - getCenter());
    direction *= m_moveSpeed * deltaTime;
    sf::Transformable::move(direction);
    m_sprite.setPosition(getPosition());
}

void Vampire::takeDamage(int damage, int attackID)
{
	// Prevents taking multiple damage from same attack
	if (m_lastAttackID == attackID)
		return;

	m_stopTimer = m_stopDuration;

	m_health -= damage;
	if (m_health <= 0)
	{
		m_health = 0;
		m_isKilled = true;
	}

	m_sound.setBuffer(*m_pGame->getVampireHitBuffer());
	m_sound.play();

	m_lastAttackID = attackID;
}