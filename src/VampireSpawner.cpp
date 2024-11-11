#include "VampireSpawner.h"

VampireSpawner::VampireSpawner(Game* game) :
	m_pGame(game)
{
}

void VampireSpawner::update(float deltaTime)
{
	updateSpawn(deltaTime);

	for (auto& temp : m_pVampires)
	{
		temp->update(deltaTime);
	}

	int i = 0;
    while (i < m_pVampires.size())
    {
        if (m_pVampires[i]->isKilled())
        {
			m_sound.setBuffer(*m_pGame->getVampireDeathBuffer());
			m_sound.play();

            std::swap(m_pVampires[i], m_pVampires.back());
            m_pVampires.pop_back();
            continue;
        }
        i++;
    }
}

void VampireSpawner::updateSpawn(float deltaTime)
{
	if (m_vampireSpawnTimer > 0.0f)
    {
        m_vampireSpawnTimer -= deltaTime;
        return;
    }

    float randomXPos = rand() % ScreenWidth;
    float randomYPos = rand() % ScreenHeight;

    float distToRight = (float) ScreenWidth - randomXPos;
    float distToBottom = (float) ScreenHeight - randomYPos;

    float xMinDist = randomXPos < distToRight ? -randomXPos : distToRight;
    float yMinDist = randomYPos < distToBottom ? -randomYPos : distToBottom;

    if (abs(xMinDist) < abs(yMinDist))
        randomXPos += xMinDist;
    else
        randomYPos += yMinDist;

    sf::Vector2f spawnPosition = sf::Vector2f(randomXPos, randomYPos);
	int vampireLevel = rand() % m_maximumLevel + 1;

    m_pVampires.push_back(std::make_unique<Vampire>(m_pGame, spawnPosition, vampireLevel));

    m_spawnCount++;
	if (m_spawnCount % SpawnCountToIncreaseMaxLevel == 0)
	{
		m_maximumLevel++;
	}
    if (m_vampireSpawnCooldown > MinimumVampireSpawnCooldown && m_spawnCount % SpawnCountToDecreaseCooldown == 0)
    {
        m_vampireSpawnCooldown -= VampireSpawnCooldownDecrement;
    }
    m_vampireSpawnTimer = m_vampireSpawnCooldown;
}

void VampireSpawner::initialise()
{
	m_pVampires.clear();
	m_vampireSpawnTimer = 0.0f;
	m_vampireSpawnCooldown = StartingVampireSpawnCooldown;
	m_spawnCount = 0;
	m_maximumLevel = 1;
}

void VampireSpawner::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (auto& temp : m_pVampires)
	{
		temp->draw(target, states);
	}
}