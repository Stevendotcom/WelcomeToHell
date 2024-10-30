#include "ResManager.h"

#include <string>

#include "raylib.h"

#include "Error.h"

namespace {

#pragma region Fonts

Font AlmendraDisplay;
Font MissingFont;

#pragma endregion

#pragma region Textures

Texture2D Background;
Texture2D PlayerSprite;
Texture2D DemonSpriteMove;
Texture2D BulletSprite;
Texture2D MissingTexture;
Texture2D HeartSprite;
Texture2D HeartBackground;
Texture2D Buttons;
Texture2D PauseBG;
Texture2D Btn;
Texture2D BtnPressed;

#pragma endregion

#pragma region SFX

Music MainMenuMusic;
Music GameMusic;
Music MissingMusic;
Sound Shoot;
Sound Hit;
Sound Dropship;
Sound MenuOpen;
Sound MenuHover;
Sound MissingSound;

#pragma endregion

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
    case Resources::BulletSprite:
      return "BulletSprite";
    case Resources::Last:
      return "";
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
    case Resources::BulletSprite:
      if (IsTextureReady(BulletSprite)) {
        return BulletSprite;
      }
      break;
    case Resources::HeartSprite:
      if (IsTextureReady(HeartSprite)) {
        return HeartSprite;
      }
      break;

    case Resources::HeartBackground:
      if (IsTextureReady(HeartBackground)) {
        return HeartBackground;
      }
      break;
    case Resources::Buttons:
      if (IsTextureReady(Buttons)) {
        return Buttons;
      }
      break;

    case Resources::PauseBG:
      if (IsTextureReady(PauseBG)) {
        return PauseBG;
      }
      break;
    case Resources::Btn:
      if (IsTextureReady(Btn)) {
        return Btn;
      }
      break;
    case Resources::BtnPressed:
      if (IsTextureReady(BtnPressed)) {
        return BtnPressed;
      }
      break;
    default:
      Error::UnknownResource(ResourceToString(Resource));
  }

  Error::ResourceNotReady(ResourceToString(Resource));
  return MissingTexture;
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
      Error::UnknownResource(ResourceToString(Resource));
  }

  Error::ResourceNotReady(ResourceToString(Resource));
  return MissingMusic;
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
      Error::UnknownResource(ResourceToString(Resource));
  }

  Error::ResourceNotReady(ResourceToString(Resource));
  return MissingSound;
}



Font& ResManager::GetFont(const Resources Resource) {

  switch (Resource) {
    case Resources::AlmendraDisplay:
      if (IsFontReady(AlmendraDisplay)) {
        return AlmendraDisplay;
      }
      break;

    default:
      Error::UnknownResource(ResourceToString(Resource));
  }

  Error::ResourceNotReady(ResourceToString(Resource));
  return MissingFont;
}



void ResManager::MakeFonts() {
  AlmendraDisplay = LoadFont("res/fonts/AlmendraDisplay-Regular.ttf");
}



void ResManager::MakeTextures() {
  Background = LoadTexture("res/sprites/background.png");
  PlayerSprite = LoadTexture("res/sprites/jetpack.png");
  DemonSpriteMove = LoadTexture("res/sprites/CacodaemonMoveOnly.png");
  BulletSprite = LoadTexture("res/sprites/bullet.png");
  HeartSprite = LoadTexture("res/sprites/Health&Stamina/Colors.png");
  HeartBackground = LoadTexture("res/sprites/Health&Stamina/Border.png");
  Buttons = LoadTexture(
      "res/sprites/StonePixel/Buttons/InsideFrameButtons32x32.png");
  PauseBG = LoadTexture("res/sprites/StonePixel/Frames/2.png");
  Btn = LoadTexture("res/sprites/StonePixel/Buttons/Button1/Button.png");
  BtnPressed =
      LoadTexture("res/sprites/StonePixel/Buttons/Button1/Button2.png");
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
