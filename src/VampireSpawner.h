#pragma once

#include <iostream>

#include "Game.h"
#include "Vampire.h"

class VampireSpawner
{
public:
    VampireSpawner(Game* game);
    ~VampireSpawner() {}

    // Start
    void initialise();

    // Loop
    void update(float deltaTime);
    void updateSpawn(float deltaTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    // Getters
    std::vector<std::unique_ptr<Vampire>>& getVampires() { return m_pVampires; }
    int getMaximumLevel() { return m_maximumLevel; }

private:
    // References
    Game* m_pGame;
    std::vector<std::unique_ptr<Vampire>> m_pVampires;

    // Timers
    float m_vampireSpawnTimer;
    float m_vampireSpawnCooldown;

    // Variables
    int m_spawnCount;
    int m_maximumLevel;

    // Audio
    sf::Sound m_sound;
};
