/******************************************************************
\file   GameState.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  
******************************************************************/
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameStateManager.h"


namespace GLE
{
	class GameState
	{
	public:
		virtual void Load(GameStateManager* game) = 0;
		virtual void Init() = 0;
		virtual void Cleanup() = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		virtual void HandleEvents(GameStateManager* game) = 0;
		virtual void Update(GameStateManager* game) = 0;
		virtual void Draw(GameStateManager* game) = 0;
		virtual void Unload() = 0;

		void ChangeState(GameStateManager* game, GameState* state) {
			game->ChangeState(state);
		}

	protected:
		GameState() { }
	};
}

#endif