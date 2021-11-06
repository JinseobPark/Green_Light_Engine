/******************************************************************
\file   Graphics.cpp
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief
******************************************************************/
#include "Graphics.h"
#include "DebugTool.h"// debugassert
#include "GL\glew.h" //loading opengl functions
#include "Application.h" //swap window

#include <fstream> //file stream; open file
#include <sstream> //string stream; file -> string

#include <vector>
#include "SOIL.h"
namespace GLE {
	Graphics* GRAPHICS = nullptr;

	GLuint CreateShader(GLenum Shadertype, const char* fileName)
	{
		std::fstream f;
		//file open
		f.open(fileName);
		bool isOpen = f.is_open();
		DEBUG_ASSERT(!isOpen, "Opening a shader file failed\n");
		std::stringstream sstream;
		// insert file stream buffer in a string stream
		sstream << f.rdbuf();

		std::string source = sstream.str();
		const char* sourceGL = source.c_str();
		GLuint shader = glCreateShader(Shadertype);
		glShaderSource(shader, 1, &sourceGL, NULL);

		//Compiling shader 
		glCompileShader(shader);

		//Check compiling 
		GLint iv;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &iv);
		if (iv != GL_TRUE)
		{
			DEBUG_PRINT("Failed to compile shader source; %s\n", fileName);
		}

		f.close();

		return shader;
	}

	Graphics::Graphics()
	{
		DEBUG_ASSERT(GRAPHICS != nullptr, "Graphics system is already existing !!!\n ");
		GRAPHICS = this;
	}

	void Graphics::Initialize()
	{
		//loading opengl functions
		DEBUG_ASSERT(glewInit() != GLEW_OK, "Initializing GLEW is failed !!!\n");

		// I am using random values 
		glClearColor(0.5f, 0.7f, 0.5f, 1.f);

		//Creating shader program
		program = glCreateProgram();

		//DEBUG_PRINT("%i", glGetError());

		//Createing vertex shader 
		GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, "vertexShader.vert");
		GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, "fragmentShader.frag");

		//Attach compiled shaders to a program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		//Try linking attached shaders
		glLinkProgram(program);

		//Detach shaders
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);

		//Delete shaders 
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		//Get the error
		GLint iv;
		int InfoLogLength;

		glGetProgramiv(program, GL_LINK_STATUS, &iv);
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (iv != GL_TRUE)
		{
			std::vector<char> message(InfoLogLength + 1);
			glGetProgramInfoLog(program, InfoLogLength, NULL, &message[0]);
			DEBUG_PRINT("Error message = %s\n", &message[0]);
			DEBUG_PRINT("Failed to link program!!!\n");
		}

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		GLuint buffer;

		GLfloat bufferData[] = {
			-0.5f, 0.5f, 0.f,  //Top Left vertex
			0.5f, 0.5f, 0.f,  //Top Right vertex
			0.5f, -0.5f, 0.f,  //Bottom right vertex
							   //-1.f, -1.f, 0.f, //Bottom left vertex

			-0.5f, 0.5f, 0.f,  //Top Left vertex
			0.5f, -0.5f, 0.f,  //Bottom right vertex
			-0.5f, -0.5f, 0.f, //Bottom left vertex

			//18
			0.f, 1.f,		  //Top left texture coordinate
			1.f, 1.f,		//Top right texture coordinate
			1.f, 0.f,		//Bottom right texture coordinate
																//0.f, 0.f,	//Bottom left texture coordinate


			0.f, 1.f,		  //Top left texture coordinate
			1.f, 0.f,		//Bottom right texture coordinate
			0.f, 0.f,	//Bottom left texture coordinate
				//30


			//0.0f, 0.0f, 0.0f, //0
			//0.0f, 0.5f, 0.0f, //1
			//0.5f, 0.0f, 0.0f, //2
			//0.0f,-0.5f, 0.0f, //4
			//42 
			//Color data
			1.f, 1.f, 1.f, 1.f, //Red
			1.f, 1.f, 1.f, 1.f, //Green
			1.f, 1.f, 1.f, 1.f,	//Blue
			1.f, 1.f, 1.f, 1.f,  //Red

			1.f, 1.f, 1.f, 1.f, //Red
			1.f, 1.f, 1.f, 1.f, //Green
			1.f, 1.f, 1.f, 1.f,	//Blue
			1.f, 1.f, 1.f, 1.f  //Red
			//48
		};

		//create opengl buffer object 
		glGenBuffers(1, &buffer);
		//bind the buffer object we generated to the GL_ARRAY_BUFFER target! 
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		//allocate memory for buffer data in GPU and 
		glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData), bufferData, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0); //Vertex
		glVertexAttribPointer(0, 3 /*x,y,z*/, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1); //Color
		glVertexAttribPointer(1, 4 /*r,g,b,a*/, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(float[30]));
		glEnableVertexAttribArray(2); //texture coordinate
		glVertexAttribPointer(2, 2 /*u,v*/, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(float[18]));

		glBindVertexArray(0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//Get uniform location
		GLuint location = glGetUniformLocation(program, "texturing");
		glUseProgram(program);
		glUniform1i(location, 1/*true*/);
		glUseProgram(0);


		//Load texture using SOIL
		GLuint textureID = SOIL_load_OGL_texture("Slime.png",
			SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_INVERT_Y);

		if (textureID == 0)
		{
			DEBUG_PRINT("image can not load");
		}
		glBindTexture(GL_TEXTURE_2D, textureID);

		uniformLocations[0] = glGetUniformLocation(program, "posOffset");
		uniformLocations[1] = glGetUniformLocation(program, "sizeOffset");


		//GLuint circleVAO;
		//glGenVertexArrays(1, &circleVAO);
		//glBindVertexArray(circleVAO);

		//GLuint circleBufferObject;
		//glGenBuffers(1, &circleBufferObject);
		//glBindBuffer(GL_VERTEX_ARRAY, circleBufferObject);
		//const int sizeVertices = numVertices * 3;
		//glBufferData(GL_VERTEX_ARRAY, sizeof(float[38 * 3]), g_circleVertexBuffer, );

		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//glBindVertexArray(circleVAO);

	}

	//All systems are updated every frame
	void Graphics::Update(float /*dt*/)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(VAO);

		//Drawing sprite
		for (std::vector<Sprite*>::iterator it = SpriteList.begin();
			it != SpriteList.end(); ++it)
		{
			glBindTexture(GL_TEXTURE_2D, (*it)->TextureID);
			//Todo : set color, animation..

			//Todo : decide 1 unit in game world
			glUniform2f(uniformLocations[0], (*it)->pTransform->GetPosition().x / Win_Width * 2, (*it)->pTransform->GetPosition().y / Win_Height * 2 );
			//Todo : apply aspect
			glUniform2f(uniformLocations[1], (*it)->Size.x * (2.f / APP->screenWidth), (*it)->Size.y * (2.f / APP->screenHeight));
			//Drawing vertex arrays
			// 1 param = how to draw the vertices
			// 2       = vertex index
			// 3       = how many vertices are drawn
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}


		glUseProgram(0);
		glBindVertexArray(0);

		APP->SwapWindow();
	}


	Graphics::~Graphics()
	{
		//Unbind
		//Todo : delete loaded textures
		glBindVertexArray(0);
		glUseProgram(0);
		glDeleteProgram(program);
	}
}
