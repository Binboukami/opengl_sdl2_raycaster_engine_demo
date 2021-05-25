#pragma once
#include "window.h"

class Renderer : public Window
{
public:
	Renderer(const Window &window);
	~Renderer();

	bool init();
	void pollEvents(SDL_Event& event);

	void clear();
	void const display();

	void drawBackground(float R, float G, float B, float A);

protected:
	SDL_Renderer* renderer = nullptr;

private:
};
