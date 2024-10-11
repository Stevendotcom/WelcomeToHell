#include "SceneManager.h"

#include <iostream>
#include <ostream>

#include "scenes/MainMenu.h"
#include "scenes/Play.h"
#include "scenes/Credits.h"

namespace SceneManager {

#pragma region Declarations

/**
 *
 */
void SceneLoop(Scenes selectedScene);

#pragma endregion



void SceneLoop(Scenes selectedScene) {
  switch (selectedScene) {
    case SceneManager::Scenes::MainMenu:

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
void ChangeScene(const Scenes SelectedScene ) {
  SceneLoop(SelectedScene);
}

} // namespace SceneManager
