#pragma once
#include <raylib.h>
#include <string>

namespace ResManager {

Texture2D& GetTexture(const std::string& Name);

Music& GetMusic(const std::string& Name);

Sound& GetSound(const std::string& Name);

Font& GetFont(const std::string& Name);

void MakeFonts();

void MakeTextures();

void MakeSounds();

void MakeMusic();

};
