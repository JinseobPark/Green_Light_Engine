/******************************************************************
\file   DebugTool.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  tool helper
******************************************************************/
#pragma once

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#ifdef _malloca
#undef _malloca
#endif
#include <Windows.h>

#include <stdlib.h>
#include <crtdbg.h>
#include <cassert>

#define DEBUG_MEMORY_LEAK_CHECKS() \
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);\
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);\
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);


#define DEBUG_CREATE_CONSOLE() \
	AllocConsole();\
	FILE *pFile;\
	freopen_s(&pFile, "CONOUT$", "a", stdout);\
	freopen_s(&pFile, "CONOUT$", "a", stderr);


#define DEBUG_DESTROY_CONSOLE() \
	fclose(pFile);\
	FreeConsole();

#define DEBUG_ASSERT(condition, expression) assert(!(condition) && (#expression));
#define DEBUG_PRINT(format, ...) do{fprintf(stdout, "%s:%d:%s(): "#format, __FILE__, __LINE__, __func__, __VA_ARGS__);}while(0)


#else
#define DEBUG_MEMORY_LEAK_CHECKS()
#define DEBUG_CREATE_CONSOLE()
#define DEBUG_DESTROY_CONSOLE()
#define DEBUG_ASSERT(condition, expression)
#define DEBUG_PRINT(format, ...)
#endif //_DEBUG


#define PI 3.1495f

