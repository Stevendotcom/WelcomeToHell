#include "ResManager.h"

#include <iostream>
#include <string>

namespace {

#pragma region Fonts

Font AlmendraDisplay;

#pragma endregion

#pragma region Textures

Texture2D Background;
Texture2D PlayerSprite;
Texture2D DemonSpriteMove;

#pragma endregion

#pragma region SFX

Music MainMenuMusic;
Music GameMusic;
Sound Shoot;
Sound Hit;
Sound Dropship;
Sound MenuOpen;
Sound MenuHover;

#pragma endregion

void ErrResourceNotReady(const std::string& Name) {
  //if it was found but is not ready
  std::cerr << "Resource Not Ready: " << Name << "\n";
}


void ErrUnknownResource(const std::string& Name) {
  std::cerr << "Unknown resource name: " << Name << "\n";
}

}


std::string ResManager::ResourceToString(const Resources Resource) {
  switch (Resource) {
    case Resources::AlmendraDisplay:
      return "AlmendraDisplay";
    case Resources::Background:
      return "Background";
    case Resources::MainMenuMusic:
      return "MainMenuMusic";
    case Resources::GameMusic:
      return "GameMusic";
    case Resources::Shoot:
      return "Shoot";
    case Resources::Hit:
      return "Hit";
    case Resources::Dropship:
      return "Dropship";
    case Resources::MenuOpen:
      return "MenuOpen";
    case Resources::MenuHover:
      return "MenuHover";
    case Resources::PlayerSprite:
      return "PlayerSprite";
    case Resources::DemonSpriteMove:
      return "DemonSpriteMove";
    default:
      return "unknown";
  }
}


Texture2D& ResManager::GetTexture(const Resources Resource) {

  switch (Resource) {
    case Resources::Background:
      if (IsTextureReady(Background)) {
        return Background;
      }
      break;

    case Resources::PlayerSprite:
      if (IsTextureReady(PlayerSprite)) {
        return PlayerSprite;
      }
      break;

    case Resources::DemonSpriteMove:
      if (IsTextureReady(DemonSpriteMove)) {
        return DemonSpriteMove;
      }
      break;

    default:
      ErrUnknownResource(ResourceToString(Resource));
      abort();
  }

  ErrResourceNotReady(ResourceToString(Resource));
  abort();
}


Music& ResManager::GetMusic(const Resources Resource) {

  switch (Resource) {
    case Resources::MainMenuMusic:
      if (IsMusicReady(MainMenuMusic)) {
        return MainMenuMusic;
      }
      break;

    case Resources::GameMusic:
      if (IsMusicReady(GameMusic)) {
        return GameMusic;
      }
      break;

    default:
      ErrUnknownResource(ResourceToString(Resource));
      abort();

  }

  ErrResourceNotReady(ResourceToString(Resource));
  abort();

}


Sound& ResManager::GetSound(const Resources Resource) {

  switch (Resource) {
    case Resources::Shoot:
      if (IsSoundReady(Shoot)) {
        return Shoot;
      }
      break;

    case Resources::Hit:
      if (IsSoundReady(Hit)) {
        return Hit;
      }
      break;

    case Resources::Dropship:
      if (IsSoundReady(Dropship)) {
        return Dropship;
      }
      break;

    case Resources::MenuOpen:
      if (IsSoundReady(MenuOpen)) {
        return MenuOpen;
      }
      break;

    case Resources::MenuHover:
      if (IsSoundReady(MenuHover)) {
        return MenuHover;
      }
      break;

    default:
      ErrUnknownResource(ResourceToString(Resource));
      abort();
  }

  ErrResourceNotReady(ResourceToString(Resource));
  abort();
}


Font& ResManager::GetFont(const Resources Resource) {

  switch (Resource) {
    case Resources::AlmendraDisplay:
      if (IsFontReady(AlmendraDisplay)) {
        return AlmendraDisplay;
      }
      break;

    default:
      ErrUnknownResource(ResourceToString(Resource));
      abort();
  }

  ErrResourceNotReady(ResourceToString(Resource));
  abort();
}


void ResManager::MakeFonts() {
  AlmendraDisplay = LoadFont("res/fonts/AlmendraDisplay-Regular.ttf");
}


void ResManager::MakeTextures() {
  Background = LoadTexture("res/sprites/background.png");
  PlayerSprite = LoadTexture("res/sprites/jetpack.png");
  DemonSpriteMove = LoadTexture("res/sprites/CacodaemonMoveOnly.png");
}


void ResManager::MakeSounds() {

  Shoot = LoadSound("res/sfx/SnakesAuthentic/762x54r_Single_WAV.wav");
  Hit = LoadSound("res/sfx/ShapeForms/BLLTImpt_Hit Marker_07.wav");
  MenuOpen = LoadSound("res/sfx/ShapeForms/Hologram_Menu_Open-2.wav");
  MenuHover = LoadSound("res/sfx/ShapeForms/Old_Terminal_Popup_Appear_Low.wav");
  Dropship = LoadSound("res/sfx/PixaBay/dropship-idle-hum-84742.ogg");

}


void ResManager::MakeMusic() {

  MainMenuMusic = LoadMusicStream(
      "res/sfx/PurgatoryPack/DavidKBD-From_the_Dark_Past.ogg");
  GameMusic = LoadMusicStream("res/sfx/PurgatoryPack/DavidKBD-On_Fire.ogg");

}
