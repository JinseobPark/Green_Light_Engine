/******************************************************************
\file   GameStageManager.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  game state manager
******************************************************************/
#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "SDL.h"
#include "Systems.h"
#include <vector>
#include <memory>

namespace GLE
{
	class GameState;
	class GameStateManager
	{
	public:
		void Init();
		void Cleanup();

		void ChangeState(GameState* state);
		void PushState(GameState* state);
		void PopState();

		void HandleEvents();
		void Update(float dt);
		void Draw();

		void Unload();
		bool Running() { return m_running; }
		void Quit() { m_running = false; }

		void AddLogic(ObjectLogic* logic);

	private:

		std::vector<ObjectLogic*> LogicList;
		std::vector<GameState*> states;

		bool m_running;
		bool m_fullscreen;
	};
}

#endif