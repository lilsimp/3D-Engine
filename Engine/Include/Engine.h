#ifndef ENGINE_H
#define ENGINE_H

#include "GameStateManager.h"

class GameEngine {
	public:
		// Initialize the game engine.
		void Init(void);
	
		// Update the game engine.
		void Update(void);
	
		// Shutdown the game engine.
		void Shutdown(void);

		GameStateManager* GSM;
};

#endif
