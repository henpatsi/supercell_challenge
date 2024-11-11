#include "Game.h"

Game::Game() :
    m_state(State::WAITING),
    m_pClock(std::make_unique<sf::Clock>()),
    m_pPlayer(std::make_unique<Player>(this)),
	m_pVampireSpawner(std::make_unique<VampireSpawner>(this))
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

	// Load textures
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

	// Load music
	if (!m_music.openFromFile(ResourceManager::getFilePath("music.wav")))
	{
		std::cerr << "Unable to load music" << std::endl;
		return false;
	}
	m_music.setVolume(25);

	// Load sound effects
	if (!m_playerAttackBuffer.loadFromFile(ResourceManager::getFilePath("player_attack.wav")))
	{
		std::cerr << "Unable to load sound" << std::endl;
		return false;
	}
	if (!m_playerHitBuffer.loadFromFile(ResourceManager::getFilePath("player_hit.wav")))
	{
		std::cerr << "Unable to load sound" << std::endl;
		return false;
	}
	if (!m_playerDeathBuffer.loadFromFile(ResourceManager::getFilePath("player_death.wav")))
	{
		std::cerr << "Unable to load sound" << std::endl;
		return false;
	}
	if (!m_vampireHitBuffer.loadFromFile(ResourceManager::getFilePath("vampire_hit.wav")))
	{
		std::cerr << "Unable to load sound" << std::endl;
		return false;
	}
	if (!m_vampireDeathBuffer.loadFromFile(ResourceManager::getFilePath("vampire_death.wav")))
	{
		std::cerr << "Unable to load sound" << std::endl;
		return false;
	}

    resetLevel();
    return true;
}

void Game::resetLevel()
{
    m_pPlayer->initialise();
    m_pClock->restart();
	m_pVampireSpawner->initialise();

	m_elapsedTime = 0;

	m_xp = 0;
	m_nextUpgrade = 1;

	m_music.play();
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
			m_pVampireSpawner->update(deltaTime);

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
}

void drawSimpleFont(sf::RenderTarget &target, const sf::Font &font, std::string content, sf::Vector2f position, sf::Color color = sf::Color::White, bool bold = false)
{
	sf::Text text;
	text.setFont(font);
	text.setFillColor(color);
	if (bold)
		text.setStyle(sf::Text::Bold);
	text.setString(content);
	text.setPosition(position);
	target.draw(text);
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Draw player.
    m_pPlayer->draw(target, states);

    //  Draw world.
	m_pVampireSpawner->draw(target, states);

	 //  Draw texts.
    if (m_state == State::WAITING)
    {
       drawSimpleFont(target, m_font, 
				"Game Start!", 
				sf::Vector2f(80, 80),
				sf::Color::White,
				true);
    }
	else if (m_state == State::GAME_OVER)
	{
		drawSimpleFont(target, m_font, 
				"Game Over!", 
				sf::Vector2f(80, 80),
				sf::Color::White,
				true);

		drawSimpleFont(target, m_font, 
				"XP: " + std::to_string(m_xp) + "\nTime: " + std::to_string((int) m_elapsedTime), 
				sf::Vector2f(80, 120));
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

		drawSimpleFont(target, m_font, 
				"XP: " + std::to_string(m_xp), 
				sf::Vector2f(20, 20));

		drawSimpleFont(target, m_font, 
				"Next upgrade: " + std::to_string(m_nextUpgrade), 
				sf::Vector2f(20, 50));

		drawSimpleFont(target, m_font, 
				"Health: " + std::to_string(m_pPlayer->getHealth()), 
				sf::Vector2f(20, 150),
				sf::Color::Red);

		drawSimpleFont(target, m_font, 
				"Enemy level: " + std::to_string(m_pVampireSpawner->getMaximumLevel()), 
				sf::Vector2f(20, 100));

		if (m_state == State::UPGRADE)
		{
			sf::Text upgradeText;
			upgradeText.setFont(m_font);
			upgradeText.setFillColor(sf::Color::White);
			upgradeText.setString("Press 1, 2, or 3 to upgrade!\n\n1 : Move Speed\n2 : Damage\n3 : Attack Size\n\nCurrent speed: "
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

void Game::onVampireKilled(int level)
{
	m_xp += level;
	if (m_xp >= m_nextUpgrade)
	{
		m_state = State::UPGRADE;
		m_nextUpgrade += m_nextUpgrade * UpgradeCostMultiplier;
	}
}