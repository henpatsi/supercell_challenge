#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <iostream>

#include "Constants.h"
#include "Weapon.h"
#include "Player.h"

class Player;
class Game;

struct InputData
{
    bool m_movingUp = false;
    bool m_movingDown = false;
    bool m_movingLeft = false;
    bool m_movingRight = false;
    bool m_space = false;

    bool m_upgrade1 = false;
    bool m_upgrade2 = false;
    bool m_upgrade3 = false;

    bool hasInputs() { return m_movingUp || m_movingDown || m_movingLeft || m_movingRight || m_space;}
};

/* TODO
input handler should not have to know about player
player could instead check input handler key states
*/

class GameInput
{
public:
    GameInput(Game* pGame, Player* pPlayer);
    ~GameInput();

    // Loop
    void update(float deltaTime);
    bool upgrade();

    // Events
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);

private:
    // References
    Game* m_pGame;
    Player* m_pPlayer;

    InputData m_inputData;
};
