#include "StartUp.h"

#include "Constants.h"
#include "ResManager.h"
#include "raylib.h"

namespace {

// ReSharper disable once CppInconsistentNaming
constexpr int k_FPS = 60;



void MakeRes() {
  ResManager::MakeFonts();
  ResManager::MakeTextures();
  ResManager::MakeSounds();
  if (IsAudioDeviceReady()) {
    ResManager::MakeMusic();
  }
}

}



void StartUp::Start() {

  InitWindow(g_ScreenWidth, g_ScreenHeight, "Welcome To Hell");

  SetWindowState(FLAG_VSYNC_HINT);

  InitAudioDevice();

  SetExitKey(KEY_NULL);

  MakeRes();

  //SetTargetFPS(k_FPS);

}
