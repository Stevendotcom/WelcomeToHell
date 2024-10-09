#include "SceneManager.h"
#include "MainMenu.h"
#include "Play.h"
#include "Credits.h"

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
      break;
  }
}
void ChangeScene(Scenes selectedScene = Scenes::MainMenu) {
  SceneLoop(selectedScene);
}

} // namespace SceneManager
