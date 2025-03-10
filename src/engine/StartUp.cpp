﻿#include "StartUp.h"

#include <iostream>

#include "raylib.h"

#include "Constants.h"
#include "ResManager.h"
#include "SceneManager.h"

namespace {

void MakeRes() {
  ResManager::MakeFonts();
  ResManager::MakeTextures();
  ResManager::MakeSounds();
  ResManager::MakeMusic();
}

}



void StartUp::Start() {

  InitWindow(g_ScreenWidth, g_ScreenHeight, "Welcome To Hell");

  SetWindowState(FLAG_VSYNC_HINT);

  InitAudioDevice();

  if (!IsAudioDeviceReady()) {

#ifdef _DEBUG
    std::cerr << "Error setting up Audio device" << '\n';
    CloseWindow();
    abort();
  }
#else
    CloseWindow();
    return;
  }
#endif

  SetExitKey(KEY_NULL);

  MakeRes();

  SceneManager::ChangeScene();
}
