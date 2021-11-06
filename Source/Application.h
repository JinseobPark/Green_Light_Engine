/****************************************************
\file   Application.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  Window application by SDL
****************************************************/
/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/
//Version: 001
#pragma once

#include <SDL.h>
#include "Systems.h"
struct Win_Size
{
	const int width{ 1024 };
	const int height{ 768 };
};

struct Current_Win_Size
{
	int width{ 1024 };
	int height{ 768 };
};
const int Win_Width = 1280;
const int Win_Height = 800;
namespace GLE
{
	class Application : public Systems
	{
	public:

		Application();
		~Application();

		void Initialize(void) override;
		void Update(float dt) override;
		void SwapWindow();


		int screenWidth;		   //
		int screenHeight;		   //
								   //Todo : add other features
								   //Resolution size 
								   //Window size
								   //Get and Set Window size
								   //Fullscreen

	private:

		void PollEvents(void);
		void PollWindowEvent(SDL_Event &currEvent);
		void PollKeyboardEvent(SDL_Event &currEvent);
		//void PollMouseEvent(SDL_Event &currEvent);

		SDL_Event event;   //Events from the OS
		SDL_Window* pWnd;  //window data

		SDL_GLContext glContext;

		Current_Win_Size Current_SIze{ 1024 , 768 };
		Win_Size size_1024_768 { 1024, 768 };
		Win_Size size_1280_768 { 1280, 768 };
		Win_Size size_1280_800 { 1280, 800 };

	};
	extern Application* APP;
}// namespace GLE end





