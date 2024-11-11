#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "ResourceManager.h"
#include "InputHandler.h"
#include "Weapon.h"
#include "Player.h"
#include "Rectangle.h"
#include "Vampire.h"

Game::Game() :
    m_state(State::WAITING),
    m_pClock(std::make_unique<sf::Clock>()),
    m_pPlayer(std::make_unique<Player>(this)),
    m_vampireCooldown(2.0f),
    m_nextVampireCooldown(2.0f)
{
    m_pGameInput = std::make_unique<GameInput>(this, m_pPlayer.get());
}

Game::~Game()
{
}

bool Game::initialise()
{
    /*
        PAY ATTENTION HIVER!
            If you want to load any assets (fonts, textures) please use the pattern shown below
    */

    if (!m_font.loadFromFile(ResourceManager::getFilePath("Lavigne.ttf")))
    {
        std::cerr << "Unable to load font" << std::endl;
        return false;
    }
    if (!m_vampTexture.loadFromFile(ResourceManager::getFilePath("vampire.png")))
    {
        std::cerr << "Unable to load texture" << std::endl;
        return false;
    }
    if (!m_playerTexture.loadFromFile(ResourceManager::getFilePath("player.png")))
    {
        std::cerr << "Unable to load texture" << std::endl;
        return false;
    }

    resetLevel();
    return true;
}

void Game::resetLevel()
{
    m_pVampires.clear();

    m_pPlayer->initialise();
    m_pClock->restart();
	m_elapsedTime = 0;

	m_kills = 0;
	m_nextUpgrade = 1;
}

void Game::update(float deltaTime)
{
    switch (m_state)
    {
        case State::WAITING:
        {
            if (m_pClock->getElapsedTime().asSeconds() >= StartWaitTime)
            {
                m_state = State::ACTIVE;
                m_pClock->restart();
				m_elapsedTime = 0;
            }
        }
        break;
            
        case State::ACTIVE:
        {
            m_pGameInput->update(deltaTime);
            m_pPlayer->update(deltaTime);

            vampireSpawner(deltaTime);
            for (auto& temp : m_pVampires)
            {
                temp->update(deltaTime);
            }

            if (m_pPlayer->isDead())
            {
                m_state = State::GAME_OVER;
                m_pClock->restart();
            }

			m_elapsedTime += deltaTime;
        }
		break;

		case State::UPGRADE:
		{
			if (m_pGameInput->upgrade())
			{
				m_state = State::ACTIVE;
			}
		}
		break;

		case State::GAME_OVER:
		{
			if (m_pClock->getElapsedTime().asSeconds() >= GameOverWaitTime)
			{
				resetLevel();
				m_state = State::WAITING;
			}
		}
		break;
    }

    int i = 0;
    while (i < m_pVampires.size())
    {
        if (m_pVampires[i]->isKilled())
        {
            std::swap(m_pVampires[i], m_pVampires.back());
            m_pVampires.pop_back();
            continue;
        }
        i++;
    }
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Draw player.
    m_pPlayer->draw(target, states);

    //  Draw world.
    for (auto& temp : m_pVampires)
    {
        temp->draw(target, states);
    }

	 //  Draw texts.
    if (m_state == State::WAITING)
    {
        sf::Text startText;
        startText.setFont(m_font);
        startText.setString("Game Start!");
        startText.setFillColor(sf::Color::White);
        startText.setPosition(80.0f, 80.0f);
        startText.setStyle(sf::Text::Bold);
        target.draw(startText);
    }
	else if (m_state == State::GAME_OVER)
	{
		sf::Text gameOverText;
		gameOverText.setFont(m_font);
		gameOverText.setString("Game Over!");
		gameOverText.setFillColor(sf::Color::White);
		gameOverText.setPosition(80.0f, 80.0f);
		gameOverText.setStyle(sf::Text::Bold);
		target.draw(gameOverText);

		sf::Text scoreText;
		scoreText.setFont(m_font);
		scoreText.setString("Kills: " + std::to_string(m_kills)
							+ "\nTime: " + std::to_string((int) m_elapsedTime));
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(80.0f, 120.0f);
		target.draw(scoreText);
	}
	else
    {
        sf::Text timerText;
        timerText.setFont(m_font);
        timerText.setFillColor(sf::Color::White);
        timerText.setStyle(sf::Text::Bold);
        timerText.setString(std::to_string((int) m_elapsedTime));
        timerText.setPosition(sf::Vector2f((ScreenWidth - timerText.getLocalBounds().getSize().x) * 0.5, 20));
        target.draw(timerText);

		sf::Text killsText;
		killsText.setFont(m_font);
		killsText.setFillColor(sf::Color::White);
		killsText.setString("Kills: " + std::to_string(m_kills));
		killsText.setPosition(20, 20);
		target.draw(killsText);

		sf::Text nextUpgradeText;
		nextUpgradeText.setFont(m_font);
		nextUpgradeText.setFillColor(sf::Color::White);
		nextUpgradeText.setString("Next upgrade: " + std::to_string(m_nextUpgrade));
		nextUpgradeText.setPosition(20, 50);
		target.draw(nextUpgradeText);

		if (m_state == State::UPGRADE)
		{
			sf::Text upgradeText;
			upgradeText.setFont(m_font);
			upgradeText.setFillColor(sf::Color::White);
			upgradeText.setString("Press numbers to upgrade!\n\n1 : Speed\n2 : Damage\n3 : Attack Size\n\nCurrent speed: "
									+ std::to_string(m_pPlayer->getMoveSpeed()) 
									+ "\nCurrent damage: " + std::to_string(m_pPlayer->getWeapon()->getDamage())
									+ "\nCurrent attack size: " + std::to_string(m_pPlayer->getWeapon()->getAttackSize()));
			upgradeText.setPosition(sf::Vector2f((ScreenWidth - upgradeText.getLocalBounds().getSize().x) * 0.5, (ScreenHeight - upgradeText.getLocalBounds().getSize().y) * 0.5));
			target.draw(upgradeText);
		}
    }
}


void Game::onKeyPressed(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyPressed(key);
}

void Game::onKeyReleased(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyReleased(key);
}

Player* Game::getPlayer() const 
{
    return m_pPlayer.get();
}

void Game::vampireSpawner(float deltaTime)
{
    if (m_vampireCooldown > 0.0f)
    {
        m_vampireCooldown -= deltaTime;
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
    m_pVampires.push_back(std::make_unique<Vampire>(this, spawnPosition));

    m_spawnCount++;
    if (m_spawnCount % 5 == 0)
    {
        m_nextVampireCooldown -= 0.1f;
    }
    m_vampireCooldown = m_nextVampireCooldown;
}

void Game::onVampireKilled()
{
	m_kills++;
	if (m_kills >= m_nextUpgrade)
	{
		m_state = State::UPGRADE;
		m_nextUpgrade += m_nextUpgrade * 2;
	}
}