#pragma once


#include <iostream>

#include "Game.h"
#include "Vampire.h"

class VampireSpawner
{
	Game*	m_pGame;
	std::vector<std::unique_ptr<Vampire>> m_pVampires;

	float m_vampireCooldown;
	float m_nextVampireCooldown;
	int m_spawnCount;

	int m_levelUpSpawnCount;
	int m_level;

	public:
		VampireSpawner(Game* game);
		~VampireSpawner() {}

		void update(float deltaTime);
		void updateSpawn(float deltaTime);
		void initialise();

		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		std::vector<std::unique_ptr<Vampire>>& getVampires() { return m_pVampires; }
};
