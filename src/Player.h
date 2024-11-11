#pragma once

#include "Rectangle.h"

#include <memory>

#define SPRITE_SCALE 3.5f

struct InputData;

class Game;
class Weapon;

enum eDirection
{
    LEFT,
    RIGHT,
	UP,
	DOWN,
};

class Player : public Rectangle
{
public:
    Player(Game* pGame);
    virtual ~Player() {}
    
    bool initialise();
    void move(InputData inputData, float deltaTime);
    void attack();
	void setWeaponPosition();
    void update(float deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool isDead() const { return m_isDead; }
    void setIsDead(bool isDead) { m_isDead = isDead; }

    Weapon* getWeapon() { return m_pWeapon.get(); }

	void upgradeSpeed(float amount);
	void upgradeDamage(float amount);
	void upgradeAttackSize(float amount);

	int getMoveSpeed() const { return m_moveSpeed; }

private:
    bool    m_isDead = false;
    eDirection m_direction = LEFT;
    Game*   m_pGame;
    std::unique_ptr<Weapon> m_pWeapon;

	int m_moveSpeed;

	float m_attackCooldown;
	float m_attackTimer = 0.0f;
};
