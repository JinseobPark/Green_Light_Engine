/******************************************************************
\file   Input.cpp
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  Uses SDL2 for interpreting input and checks key status
******************************************************************/
#include "input.h"
#include "DebugTool.h"
#include <bitset>
#include "Application.h"

using namespace GLE;

namespace
{
	std::bitset<SDL_NUM_SCANCODES> s_pressed;   //Container of keys pressed
	std::bitset<SDL_NUM_SCANCODES> s_triggered; //Container of keys pressed
	std::bitset<SDL_NUM_SCANCODES> s_released;  //Container of keys pressed

}

void Input::Initialize()
{
	s_pressed.reset();
	s_triggered.reset();
	s_released.reset();
}

void Input::SetKeyPressed(SDL_Scancode key, SDL_EventType keyStatus)
{
	DEBUG_ASSERT(key < SDL_SCANCODE_UNKNOWN || key > SDL_NUM_SCANCODES, "not valid");

	if (keyStatus == SDL_KEYDOWN)	 //if the key is pressed
	{
		s_pressed[key] = true;
		s_triggered[key] = true;
	}
	else if (keyStatus == SDL_KEYUP)
	{
		s_released[key] = true;
		s_pressed[key] = false;
	}
}

void Input::Reset(void)
{
	s_triggered.reset();
	s_released.reset();
}

bool Input::IsPressed(SDL_Scancode key)
{
	return s_pressed[key];
}
bool Input::IsTriggered(SDL_Scancode key)
{
	return s_triggered[key];
}
bool Input::IsReleased(SDL_Scancode key)
{
	return s_released[key];
}

bool Input::IsAnyPressed(void)
{
	return s_pressed.any();
}
bool Input::IsAnyTriggered(void)
{
	return s_triggered.any();
}
bool Input::IsAnyReleased(void)
{
	return s_released.any();
}

Vector2 Input::GetMousePosition(void)
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);

	x -= APP->screenWidth / 2;
	y = -y + APP->screenHeight / 2;


	return Vector2(x, y);
}