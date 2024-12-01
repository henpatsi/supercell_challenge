#include "Player.h"

Player::Player(Game* pGame) :
	Rectangle(sf::Vector2f(PlayerWidth, PlayerHeight)),
	m_pGame(pGame),
	m_pWeapon(std::make_unique<Weapon>()),
	m_pHealthBar(std::make_unique<HealthBar>(PlayerStartingHealth))
{
	setOrigin(sf::Vector2f(0.0f, 0.0f));
}


// Start


bool Player::initialise()
{
	m_sprite.setTexture(*m_pGame->getPlayerTexture());
	m_sprite.setScale(SPRITE_SCALE, SPRITE_SCALE);
	setPosition(ScreenWidth / 2, ScreenHeight / 2);
	m_sprite.setPosition(getPosition());
	m_pWeapon->setActive(false);

	m_isDead = false;
	m_health = PlayerStartingHealth;
	m_moveSpeed = PlayerStartingMoveSpeed;

	m_damageCooldown = PlayerStartingDamageCooldown;
	m_damageTimer = 0.0f;
	m_attackCooldown = PlayerStartingAttackCooldown;
	m_attackTimer = 0.0f;

	m_pWeapon->initialize();

	m_pHealthBar->setPosition(getCenter() + sf::Vector2f(0, -m_sprite.getGlobalBounds().height * 0.5f - 20));
	m_pHealthBar->updateHealth(m_health);

	return true;
}


// Loop


void Player::update(float deltaTime)
{
	m_sprite.setPosition(getPosition());
	setWeaponPosition();
	m_pWeapon->update(deltaTime);

	if (m_attackTimer > 0.0f)
		m_attackTimer -= deltaTime;
	if (m_damageTimer > 0.0f)
		m_damageTimer -= deltaTime;
	
	m_pHealthBar->setPosition(getCenter() + sf::Vector2f(0, -m_sprite.getGlobalBounds().height * 0.5f - 20));
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	Rectangle::draw(target, states);
	m_pWeapon->draw(target, states);
}


// Functionality


void Player::move(InputData inputData, float deltaTime)
{
	float xSpeed = 0.0f;
	float ySpeed = 0.0f;
	
	xSpeed -= inputData.m_movingLeft * m_moveSpeed;
	xSpeed += inputData.m_movingRight * m_moveSpeed;
	xSpeed *= deltaTime;

	ySpeed -= inputData.m_movingUp * m_moveSpeed;
	ySpeed += inputData.m_movingDown * m_moveSpeed;
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
	}
}

void Player::attack()
{
	if (m_attackTimer > 0.0f)
		return;
	m_attackTimer = m_attackCooldown;

	if (m_direction == LEFT || m_direction == RIGHT)
		m_pWeapon->setActive(true);
	else
		m_pWeapon->setActive(true, true);

	m_sound.setBuffer(*m_pGame->getPlayerAttackBuffer());
	m_sound.play();
}

void Player::takeDamage(int damage)
{
	if (m_damageTimer > 0.0f)
		return;
	m_damageTimer = m_damageCooldown;

	m_health -= damage;
	if (m_health <= 0)
	{
		m_health = 0;
		m_isDead = true;
	}

	m_sound.setBuffer(*m_pGame->getPlayerHitBuffer());
	m_sound.play();

	m_pHealthBar->updateHealth(m_health);
	m_pHealthBar->setPosition(getCenter() + sf::Vector2f(0, -m_sprite.getGlobalBounds().height * 0.5f - 20));
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


// Upgrades


void Player::upgradeSpeed(float amount)
{
	m_moveSpeed += amount;
}

void Player::upgradeDamage(float amount)
{
	m_pWeapon->upgradeDamage(amount);
}

void Player::upgradeAttackSize(float amount)
{
	m_pWeapon->upgradeAttackSize(amount);
}
