#pragma once
#include <string>

#include "raylib.h"

namespace ResManager {

enum class Resources {
  AlmendraDisplay,
  Background,
  MainMenuMusic,
  GameMusic,
  Shoot,
  Hit,
  Dropship,
  MenuOpen,
  MenuHover,
  PlayerSprite,
  DemonSpriteMove,
  BulletSprite,
  HeartSprite,
  HeartBackground,
  Buttons,
  PauseBG,
  Btn,
  BtnPressed,
  OneUp,
  Diamond,
  Batteries,
  Beholder,
  Mouse,
  Last
};



Texture2D& GetTexture(Resources Resource);

Music& GetMusic(Resources Resource);

Sound& GetSound(Resources Resource);

Font& GetFont(Resources Resource);

void MakeFonts();

void MakeTextures();

void MakeSounds();

void MakeMusic();

std::string ResourceToString(Resources Resource);
};
