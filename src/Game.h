#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <iostream>

#include "Constants.h"
#include "VampireSpawner.h"
#include "ResourceManager.h"
#include "InputHandler.h"
#include "Weapon.h"
#include "Player.h"
#include "Rectangle.h"
#include "Vampire.h"

class Player;
class Game;
class GameInput;
class Vampire;
class VampireSpawner;

namespace sf { class Clock; }

class Game : public sf::Drawable
{
public:

    enum class State
    {
        WAITING,
        ACTIVE,
        UPGRADE,
        GAME_OVER,
    };

    Game();
    ~Game();

    // Start
    bool initialise();
    void resetLevel();

    // Loop
    void update(float deltaTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    // Events
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);
    void onVampireKilled(int level);

    // Getters
    State getState() const { return m_state; }
    Player* getPlayer() const;

    sf::Texture* getPlayerTexture() { return &m_playerTexture; }
    sf::Texture* getVampireTexture() { return &m_vampTexture; }

    sf::SoundBuffer* getVampireDeathBuffer() { return &m_vampireDeathBuffer; }
    sf::SoundBuffer* getVampireHitBuffer() { return &m_vampireHitBuffer; }
    sf::SoundBuffer* getPlayerDeathBuffer() { return &m_playerDeathBuffer; }
    sf::SoundBuffer* getPlayerHitBuffer() { return &m_playerHitBuffer; }
    sf::SoundBuffer* getPlayerAttackBuffer() { return &m_playerAttackBuffer; }

private:
    // References
    std::unique_ptr<sf::Clock> m_pClock;
    std::unique_ptr<GameInput> m_pGameInput;
    std::unique_ptr<Player> m_pPlayer;
    std::unique_ptr<VampireSpawner> m_pVampireSpawner;

    // Variables
    State m_state;
    float m_elapsedTime;
    int m_xp;
    int m_nextUpgrade;

    // Fonts
    sf::Font m_font;
    sf::Texture m_vampTexture;
    sf::Texture m_playerTexture;

    // Audio
    sf::Music m_music;
    sf::SoundBuffer m_vampireDeathBuffer;
    sf::SoundBuffer m_vampireHitBuffer;
    sf::SoundBuffer m_playerDeathBuffer;
    sf::SoundBuffer m_playerHitBuffer;
    sf::SoundBuffer m_playerAttackBuffer;
};
