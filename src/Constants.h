#pragma once

// Game
const int ScreenWidth = 1600;
const int ScreenHeight = 1200;

const float StartWaitTime = 1.0f;
const float GameOverWaitTime = 3.0f;

// Player
const float PlayerHeight = 55.0f;
const float PlayerWidth = 55.0f;

const int PlayerStartingHealth = 100;
const float PlayerStartingMoveSpeed = 100.0f;
const float PlayerStartingAttackCooldown = 0.5f;
const float PlayerStartingAttackSize = 1.0f;
const float PlayerStartingDamage = 10;
const float PlayerStartingDamageCooldown = 0.5f;

// Upgrade
const float UpgradeCostMultiplier = 1.1f;
const int MoveSpeedUpgradeAmount = 20;
const int DamageUpgradeAmount = 10;
const float AttackSizeUpgradeAmount = 0.2f;

// Vampire
const float VampireHeight = 32.0f;
const float VampireWidth = 32.0f;

const float VampireBaseSpeed = 100.0f;
const float VampireBaseHealth = 20.0f;
const float VampireBaseDamage = 10.0f;

// VampireSpawner
const float StartingVampireSpawnCooldown = 2.0f;
const float VampireSpawnCooldownDecrement = 0.1f;
const float MinimumVampireSpawnCooldown = 0.5f;
const int SpawnCountToIncreaseMaxLevel = 10;
const int SpawnCountToDecreaseCooldown = 5;

