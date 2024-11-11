#pragma once

#include <iostream>

#include "Game.h"
#include "Vampire.h"

class VampireSpawner
{
	Game*	m_pGame;
	std::vector<std::unique_ptr<Vampire>> m_pVampires;

	float m_vampireSpawnTimer;
	float m_vampireSpawnCooldown;
	int m_spawnCount;

	int m_maximumLevel;

	sf::Sound m_sound;

	public:
		VampireSpawner(Game* game);
		~VampireSpawner() {}

		void update(float deltaTime);
		void updateSpawn(float deltaTime);
		void initialise();

		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		std::vector<std::unique_ptr<Vampire>>& getVampires() { return m_pVampires; }
		int getMaximumLevel() { return m_maximumLevel; }
};
