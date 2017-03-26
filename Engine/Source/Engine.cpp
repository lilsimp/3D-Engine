#include <iostream>

#include "main.h"
#include "Engine.h"
#include "FrameTime.h"
#include "GameStateManager.h"
#include "Render.h"

// Initialize the game engine.
void GameEngine::Init() {
	//--------------------------------------------------------------------------
	// NOTE: Certain modules need to be initialized first.
	//--------------------------------------------------------------------------

	GSM = new GameStateManager();

	FrameTimeStart();

	// Initialize the game state manager.
	GSM->Init();

	RenderInit();

	FrameTimeEnd();
}

// Update the game engine.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameEngine::Update() {
	FrameTimeStart();

	// Update the game state manager.
	GSM->Update();

	FrameTimeEnd();

	std::cout << FrameTimeGetElapsed() << std::endl;
}

// Shutdown the game engine.
void GameEngine::Shutdown() {
	// Shutdown the game state manager.
	GSM->Shutdown();

	RenderShutdown();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

