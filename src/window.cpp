#include <iostream>
#include "window.h"

Window::Window(const std::string & TITLE, int WIDTH, int HEIGHT) : TITLE(TITLE), WIDTH(WIDTH), HEIGHT(HEIGHT)
{
	if (!init())
	{
		CLOSED = true;
	}
}
Window::~Window()
{
	glfwTerminate();
	SDL_GL_DeleteContext(window);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Window::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Failed to initliaze SDL. \n" << std::endl;
		return 0;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

	if (!glfwInit())
	{
		std::cerr << "Failed to initiliaze OpenGL[GLFW]. \n" << std::endl;
		return 0;
	}

	window = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	glcontext = SDL_GL_CreateContext(window);
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (window == nullptr)
	{
		std::cerr << "Failed to create window.\n" << std::endl;
		return 0;
	}
	return 1;
}

void Window::pollEvents(SDL_Event &event)
{
		switch (event.type)
		{
		case SDL_QUIT:
			CLOSED = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				CLOSED = true;
			}
			break;
		}
}