#include <iostream>
#include "window.h"
#include "renderer.h"
#include "raycaster.h"

Window window("DEMO | Raycaster Engine", 800, 600);
Renderer renderer(window);
Raycaster raycaster(renderer);

void post()
{
	renderer.clear();
	renderer.drawBackground(0.25, 0.25, 0.25, 1);
	raycaster.drawRays();
	renderer.display();
}

void pollEvents(Window& window, Renderer& renderer)
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		renderer.pollEvents(event);
		window.pollEvents(event);
		raycaster.input(event);
	}
}
int main(int argc, char* argv[])
{
	//currently loads mapA
	raycaster.loadArray();
	while (!window.isClosed())
	{
		post();
		pollEvents(window, renderer);
	}
	return 0;
}
