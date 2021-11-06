/******************************************************************
\file   Input.cpp
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  Uses SDL2 for interpreting input and checks key status
******************************************************************/
#pragma once


#include <SDL.h>
#include "Vector2.h"

namespace GLE
{
	class Input
	{
	public:

		static void Initialize();
		static void Reset(void);

		//Sets pressed, triggered, released, or unpressed status of a key
		static void SetKeyPressed(SDL_Scancode key, SDL_EventType keyStatus);

		//Checks if a specific key is pressed, triggered, of released
		static bool IsPressed(SDL_Scancode key);
		static bool IsTriggered(SDL_Scancode key);
		static bool IsReleased(SDL_Scancode key);

		static bool IsAnyPressed(void);
		static bool IsAnyTriggered(void);
		static bool IsAnyReleased(void);

		static Vector2 GetMousePosition(void);
	};
}