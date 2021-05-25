#pragma once
#include <string>
#include <SDL.h>
#include <GLFW/glfw3.h>
#include <SDL_opengl.h>

class Window
{
public:
	Window(const std::string &TITLE, const GLint WIDTH, const GLint HEIGHT);
	~Window();

	bool init();
	void pollEvents(SDL_Event &event);

	bool CLOSED;
	inline const bool isClosed() { return CLOSED; }


protected:
	const GLint WIDTH = 800, HEIGHT = 600;

	SDL_Window* window = nullptr;
	SDL_GLContext glcontext;

private:
	const std::string TITLE;
};
