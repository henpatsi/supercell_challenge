#pragma once

#include "Rectangle.h"

class Game;

class Vampire : public Rectangle
{
public:
    Vampire(Game* game, sf::Vector2f position);
    virtual ~Vampire() {}
    
    void update(float deltaTime);
	void move(float deltaTime);

	void takeDamage(int damage, int attackID);
    bool isKilled() { return m_isKilled; }

private:
    Game* m_pGame;
    bool m_isKilled = false;

	int m_health = 20;

	float m_stopDuration = 0.2f;
	float m_stopTimer = 0.0f;

	int m_lastAttackID = 0;
};
