#include "InputHandler.h"

GameInput::GameInput(Game* pGame, Player* pPlayer) :
    m_pGame(pGame), m_pPlayer(pPlayer)
{
}

GameInput::~GameInput()
{
}


// Loop


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

bool GameInput::upgrade()
{
    if (m_inputData.m_upgrade1)
    {
        m_pPlayer->upgradeSpeed(MoveSpeedUpgradeAmount);
        m_inputData.m_upgrade1 = false;
        return true;
    }
    else if (m_inputData.m_upgrade2)
    {
        m_pPlayer->upgradeDamage(DamageUpgradeAmount);
        m_inputData.m_upgrade2 = false;
        return true;
    }
    else if (m_inputData.m_upgrade3)
    {
        m_pPlayer->upgradeAttackSize(AttackSizeUpgradeAmount);
        m_inputData.m_upgrade3 = false;
        return true;
    }

    return false;
}


// Events


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
        m_inputData.m_space = true;
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
