#include "ResManager.h"

#include <iostream>
#include <string>

namespace {

#pragma region Fonts

Font AlmendraDisplay;

#pragma endregion

#pragma region Textures

Texture2D Background;

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



Texture2D& ResManager::GetTexture(const std::string& Name) {

  switch (Name) {
    case "Background":
      if (IsTextureReady(Background)) {
        return Background;
      }
      break;

    default:
      ErrUnknownResource(Name);
      abort();
  }

  ErrResourceNotReady(Name);
  abort();
}



Music& ResManager::GetMusic(const std::string& Name) {

  switch (Name) {
    case "MainMenuMusic":
      if (IsMusicReady(MainMenuMusic)) {
        return MainMenuMusic;
      }
      break;

    case "GameMusic":
      if (IsMusicReady(GameMusic)) {
        return GameMusic;
      }
      break;

    default:
      ErrUnknownResource(Name);
      abort();

  }

  ErrResourceNotReady(Name);
  abort();

}



Sound& ResManager::GetSound(const std::string& Name) {

  switch (Name) {
    case "Shoot":
      if (IsSoundReady(Shoot)) {
        return Shoot;
      }
      break;

    case "Hit":
      if (IsSoundReady(Hit)) {
        return Hit;
      }
      break;

    case "Dropship":
      if (IsSoundReady(Dropship)) {
        return Dropship;
      }
      break;

    case "MenuOpen":
      if (IsSoundReady(MenuOpen)) {
        return MenuOpen;
      }
      break;

    case "MenuHover":
      if (IsSoundReady(MenuHover)) {
        return MenuHover;
      }
      break;

    default:
      ErrUnknownResource(Name);
      abort();
  }

  ErrResourceNotReady(Name);
  abort();
}



Font& ResManager::GetFont(const std::string& Name) {

  switch (Name) {
    case "AlmendraDisplay":
      if (IsFontReady(AlmendraDisplay)) {
        return AlmendraDisplay;
      }
      break;

    default:
      ErrUnknownResource(Name);
      abort();
  }

  ErrResourceNotReady(Name);
  abort();
}



void ResManager::MakeFonts() {
  AlmendraDisplay = LoadFont("res/fonts/AlmendraDisplay-Regular.ttf");
}



void ResManager::MakeTextures() {
  Background = LoadTexture("res/sprites/background.png");
}



void ResManager::MakeSounds() {

  Shoot = LoadSound("res/SnakesAuthentic/762x54r_Single_WAV.wav");
  Hit = LoadSound("res/ShapeForms/BLLTImpt_Hit Marker_07.wav");
  MenuOpen = LoadSound("res/ShapeForms/Hologram_Menu_Open-2.wav");
  MenuHover = LoadSound("res/ShapeForms/Old_Terminal_Popup_Appear_Low.wav");
  Dropship = LoadSound("res/PixaBay/dropship-idle-hum-84742.wav");

}



void ResManager::MakeMusic() {

  MainMenuMusic = LoadMusicStream("res/sfx/DavidKBD-From_the_Dark_Past.ogg");
  GameMusic = LoadMusicStream("res/sfx/DavidKBD-On_Fire.ogg");

}
