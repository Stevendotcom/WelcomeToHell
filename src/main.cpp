﻿#include "engine/CloseUp.h"
#include "engine/SceneManager.h"
#include "engine/StartUp.h"



int main() {
  StartUp::Start();
  SceneManager::ChangeScene();
  CloseUp::Close();
}
