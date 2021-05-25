#include <iostream>
#include "renderer.h"
#include "raycaster.h"

Renderer::Renderer(const Window &window) : Window(window)
{
	if (!init())
	{
		CLOSED = true;
	}
}
Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
	SDL_GL_DeleteContext(renderer);
}

bool Renderer::init()
{
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer = nullptr)
	{
	std::cerr << "Failed to initialize SDL.Renderer.\n" << std::endl;
	return 0;
	}
}

void Renderer::pollEvents(SDL_Event &event)
{

}


void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void const Renderer::display()
{
	SDL_GL_SwapWindow(window);
}

void Renderer::drawBackground(float R, float G, float B, float A)
{
	glClearColor(R, G, B, A);
}