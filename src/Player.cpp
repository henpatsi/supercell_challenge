#include "Player.h"
#include "Weapon.h"
#include "InputHandler.h"
#include "Constants.h"
#include <vector>
#include "Game.h"

Player::Player(Game* pGame) :
    Rectangle(sf::Vector2f(PlayerWidth, PlayerHeight)),
    m_pGame(pGame),
    m_pWeapon(std::make_unique<Weapon>())
{
    setOrigin(sf::Vector2f(0.0f, 0.0f));
}

bool Player::initialise()
{
    m_sprite.setTexture(*m_pGame->getPlayerTexture());
    m_sprite.setScale(SPRITE_SCALE, SPRITE_SCALE);
    setIsDead(false);
    setPosition(ScreenWidth / 2, ScreenHeight / 2);
    m_sprite.setPosition(getPosition());
	m_pWeapon->setActive(false);
    return true;
}

void Player::move(InputData inputData, float deltaTime)
{
    float xSpeed = 0.0f;
    float ySpeed = 0.0f;
    
    xSpeed -= inputData.m_movingLeft * PlayerSpeed;
    xSpeed += inputData.m_movingRight * PlayerSpeed;
    xSpeed *= deltaTime;

    ySpeed -= inputData.m_movingUp * PlayerSpeed;
    ySpeed += inputData.m_movingDown * PlayerSpeed;
    ySpeed *= deltaTime;
    
    sf::Transformable::move(sf::Vector2f(xSpeed, ySpeed));
    setPosition(std::clamp(getPosition().x, 0.0f, (float)ScreenWidth - PlayerWidth), std::clamp(getPosition().y, 0.0f, (float)ScreenHeight - PlayerHeight * SPRITE_SCALE)); // TODO why scale only for height?

	if (m_pWeapon->isActive() == false)
	{
		if (inputData.m_movingRight == true && inputData.m_movingLeft == false)
			m_direction = RIGHT;
		else if (inputData.m_movingRight == false && inputData.m_movingLeft == true)
			m_direction = LEFT;
		else if (inputData.m_movingUp == true && inputData.m_movingDown == false)
			m_direction = UP;
		else if (inputData.m_movingUp == false && inputData.m_movingDown == true)
			m_direction = DOWN;
		else
			m_direction = RIGHT;
    }
}

void Player::attack()
{
	if (m_direction == LEFT || m_direction == RIGHT)
    	m_pWeapon->setActive(true);
	else
		m_pWeapon->setActive(true, true);
}

void Player::update(float deltaTime)
{
    m_sprite.setPosition(getPosition());
	setWeaponPosition();
    m_pWeapon->update(deltaTime);
}

void Player::setWeaponPosition()
{
	sf::Vector2f weaponSize = m_pWeapon->getSize();
	float weaponX = 0.0f;
	float weaponY = 0.0f;
	float rotation = 0.0f;

	switch (m_direction)
	{
		case LEFT:
			weaponX = getCenter().x - weaponSize.x;
			weaponY = getCenter().y - weaponSize.y / 2.0f;
			break;
		case RIGHT:
			weaponX = getCenter().x;
			weaponY = getCenter().y - weaponSize.y / 2.0f;
			break;
		case UP:
			weaponX = getCenter().x - weaponSize.x / 2.0f;
			weaponY = getCenter().y - weaponSize.y;
			break;
		case DOWN:
			weaponX = getCenter().x - weaponSize.x / 2.0f;
			weaponY = getCenter().y;
			break;
	}

	m_pWeapon->setPosition(sf::Vector2f(weaponX, weaponY));
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    Rectangle::draw(target, states);
    m_pWeapon->draw(target, states);
}