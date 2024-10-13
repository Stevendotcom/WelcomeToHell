#include "StartUp.h"

#include "Constants.h"
#include "ResManager.h"
#include "raylib.h"

namespace {

// ReSharper disable once CppInconsistentNaming
constexpr int kFPS = 60;



void MakeRes() {
  ResManager::MakeFonts();
  ResManager::MakeTextures();
  ResManager::MakeSounds();
  ResManager::MakeMusic();
}

}



void StartUp::Start() {

  InitWindow(g_ScreenWidth, g_ScreenHeight, "Welcome To Hell");

  InitAudioDevice();

  SetExitKey(KEY_NULL);

  MakeRes();

  //SetTargetFPS(kFPS);

}
