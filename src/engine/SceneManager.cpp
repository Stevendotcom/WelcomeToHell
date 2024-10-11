#include "SceneManager.h"

#include <iostream>

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
      std::cerr << "Scene not found!" << std::endl;
      break;
  }

}

}

namespace SceneManager {

void ChangeScene(const Scenes SelectedScene) {
  SceneLoop(SelectedScene);
}

} // namespace SceneManager
