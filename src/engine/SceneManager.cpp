#include "SceneManager.h"

#include <iostream>

#include "Error.h"
#include "scenes/Play.h"

namespace {

void SceneLoop(const SceneManager::Scenes SelectedScene) {

  switch (SelectedScene) {
    case SceneManager::Scenes::MainMenu:
      //MainMenu();
      Play::Play();
      break;
    case SceneManager::Scenes::Play:
      break;
    case SceneManager::Scenes::Credits:
      break;
    case SceneManager::Scenes::Exit:
      break;
    default:
      Error::Unhandled(__LINE__, __FILE__);
      break;
  }

}

}



void SceneManager::ChangeScene(const Scenes SelectedScene) {
  SceneLoop(SelectedScene);
}
