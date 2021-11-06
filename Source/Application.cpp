/****************************************************
\file   Application.cpp
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  Window application by SDL
****************************************************/
#include "Application.h"
#include "DebugTool.h"
#include "Engine.h"
#include "input.h"
using namespace GLE;
namespace GLE
{
	Application* APP = nullptr;
}

Application::Application() : screenWidth(Win_Width), screenHeight(Win_Height), pWnd(nullptr)
{
	DEBUG_ASSERT(APP != nullptr, "No more than 1 instance of Application system!")
		APP = this;
}

Application::~Application()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(pWnd);
	pWnd = nullptr;

	SDL_Quit();
}

void Application::Initialize()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		DEBUG_PRINT("SDL couldn't initialize! SD_Error: %s\n", SDL_GetError());
	}

	pWnd = SDL_CreateWindow(
		"Help me !!!",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		screenWidth,
		screenHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
	);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	DEBUG_ASSERT(pWnd == nullptr, "window is failed!");

	glContext = SDL_GL_CreateContext(pWnd);
	/*
	check SDL_WINDOW_OPENGL or
	Graphics Driver suppoert the minor or major GL version
	Force GPU to use .exe file not on board Graphic!
	*/
	DEBUG_ASSERT(glContext == nullptr, "opengl is failed!");
}

void Application::Update(float /*dt*/)
{
	Input::Reset();
	//Todo : PollEvents
	PollEvents();

	if (Input::IsPressed(SDL_SCANCODE_ESCAPE))
	{
		ENGINE->Quit();
	}
	//if (Input::IsPressed(SDL_SCANCODE_SPACE))
	//	printf("Fuck!!!!");
	//if (Input::IsReleased(SDL_SCANCODE_SPACE))
	//	printf("Release!!!!");
	//if (Input::IsAnyTriggered())
	//	printf("Trigger!!!!");


}


void Application::PollEvents()
{
	while (SDL_PollEvent(&event))
	{
		PollWindowEvent(event);
		PollKeyboardEvent(event);
		//PollMouseEvents
	}
}

void Application::PollWindowEvent(SDL_Event &currEvent)
{
	switch (currEvent.type)
	{
	case SDL_QUIT:
		ENGINE->Quit();
		break;
	default:
		break;
	}
}

void Application::PollKeyboardEvent(SDL_Event &currEvent)
{
	switch (currEvent.type)
	{
	case SDL_KEYDOWN:
		Input::SetKeyPressed(currEvent.key.keysym.scancode, SDL_KEYDOWN);
		break;
	case SDL_KEYUP:
		Input::SetKeyPressed(currEvent.key.keysym.scancode, SDL_KEYUP);
		break;
	default:
		break;
	}
}

void Application::SwapWindow()
{
	SDL_GL_SwapWindow(pWnd);
}