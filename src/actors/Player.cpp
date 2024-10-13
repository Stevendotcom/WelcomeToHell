#include "Player.h"

#include "Constants.h"
#include "engine/ResManager.h"

namespace {

constexpr float k_MaxSpeed = 500.0F;
constexpr float k_DefRadius = 10.0F;
constexpr int k_DefHearts = 3;

}



void Player::Initialize(Player& Player) {
  Player = {0.0f,
            k_DefRadius,
            k_DefHearts,
            {g_ScreenWidth / 2.0F, g_ScreenHeight / 2.0F},
            {0.0F, 1.0F},
            GetTexture(ResManager::Resources::PlayerSprite)};
}

