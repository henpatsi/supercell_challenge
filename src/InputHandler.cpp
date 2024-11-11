#include "InputHandler.h"
#include "Weapon.h"
#include "Player.h"

GameInput::GameInput(Game* pGame, Player* pPlayer) :
    m_pGame(pGame), m_pPlayer(pPlayer)
{

    
}

GameInput::~GameInput()
{
    
}

void GameInput::update(float deltaTime)
{
    if (m_inputData.hasInputs())
    {
        m_pPlayer->move(m_inputData, deltaTime);
    }

    if (m_inputData.m_space)
    {
        m_pPlayer->attack();
    }
}

void GameInput::upgrade()
{
	if (m_inputData.m_upgrade1)
	{
		m_pPlayer->upgradeSpeed(20);
		m_inputData.m_upgrade1 = false;
	}
	else if (m_inputData.m_upgrade2)
	{
		m_pPlayer->upgradeDamage(10);
		m_inputData.m_upgrade2 = false;
	}
	else if (m_inputData.m_upgrade3)
	{
		m_pPlayer->upgradeAttackSize(0.05);
		m_inputData.m_upgrade3 = false;
	}
}

void GameInput::onKeyPressed(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
    {
        m_inputData.m_movingUp = true;
    }
    else if (key == sf::Keyboard::Down)
    {
        m_inputData.m_movingDown = true;
    }
    else if (key == sf::Keyboard::Left)
    {
        m_inputData.m_movingLeft = true;
    }
    else if (key == sf::Keyboard::Right)
    {
        m_inputData.m_movingRight = true;
    }
    else if (key == sf::Keyboard::Space)
    {
        if (m_inputData.m_spaceReleased)
        {
            m_inputData.m_space = true;
        }
        m_inputData.m_spaceReleased = false;
    }
	else if (key == sf::Keyboard::Num1)
	{
		m_inputData.m_upgrade1 = true;
	}
	else if (key == sf::Keyboard::Num2)
	{
		m_inputData.m_upgrade2 = true;
	}
	else if (key == sf::Keyboard::Num3)
	{
		m_inputData.m_upgrade3 = true;
	}
}

void GameInput::onKeyReleased(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
    {
        m_inputData.m_movingUp = false;
    }
    else if (key == sf::Keyboard::Down)
    {
        m_inputData.m_movingDown = false;
    }
    else if (key == sf::Keyboard::Left)
    {
        m_inputData.m_movingLeft = false;
    }
    else if (key == sf::Keyboard::Right)
    {
        m_inputData.m_movingRight = false;
    }
    else if (key == sf::Keyboard::Space)
    {
        m_inputData.m_space = false;
        m_inputData.m_spaceReleased = true;
    }
	else if (key == sf::Keyboard::Num1)
	{
		m_inputData.m_upgrade1 = false;
	}
	else if (key == sf::Keyboard::Num2)
	{
		m_inputData.m_upgrade2 = false;
	}
	else if (key == sf::Keyboard::Num3)
	{
		m_inputData.m_upgrade3 = false;
	}
}
