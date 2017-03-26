#include "main.h"
#include "Engine.h"
#include "GameStateManager.h"
#include "System.h"

GLFWwindow* window;

int main(void) {
	GameEngine game;

	System_Initialize();

	game.Init();

	while (game.GSM->IsRunning()) {
		game.Update();
	}

	System_Exit();

}