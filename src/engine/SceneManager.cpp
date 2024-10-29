#include "SceneManager.h"

#include <iostream>

#include "CloseUp.h"
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
      CloseUp::Close();
      break;
    default:
      CloseUp::Close();
      Error::Unhandled(__LINE__, __FILE__);
      break;
  }

}

}



void SceneManager::ChangeScene(const Scenes SelectedScene) {
  SceneLoop(SelectedScene);
}
