#include "Vampire.h"
#include "Constants.h"
#include "Game.h"
#include "Weapon.h"
#include "Player.h"
#include "MathUtils.h"

Vampire::Vampire(Game* game, sf::Vector2f position) :
    Rectangle(sf::Vector2f(VampireWidth, VampireHeight)),
    m_pGame(game)
{
    setPosition(position);
    setOrigin(sf::Vector2f(0.0f, 0.0f));
    m_isKilled = false;

    m_sprite.setTexture(*m_pGame->getVampireTexture());
    m_sprite.setScale(2.0f, 2.0f);
}

void Vampire::update(float deltaTime)
{
    if (m_isKilled)
        return;
    
    Player* pPlayer = m_pGame->getPlayer();

    if (collidesWith(pPlayer->getWeapon()))
    {
        takeDamage(pPlayer->getWeapon()->getDamage(), pPlayer->getWeapon()->getAttackID());
		if (m_isKilled)
			m_pGame->onVampireKilled();
        return;
    }

    if (collidesWith(pPlayer))
        pPlayer->setIsDead(true);

	if (m_stopTimer > 0.0f)
		m_stopTimer -= deltaTime;
	else
		move(deltaTime);
}

void Vampire::move(float deltaTime)
{
	sf::Vector2f playerCenter = m_pGame->getPlayer()->getCenter();
    sf::Vector2f direction = VecNormalized(playerCenter - getCenter());
    direction *= VampireSpeed * deltaTime;
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

	m_lastAttackID = attackID;
}