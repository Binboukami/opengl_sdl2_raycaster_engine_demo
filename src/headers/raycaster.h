#pragma once
#include <math.h>
#include "renderer.h"

#define PI 3.141592
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533 //degree in radians

class Raycaster : public Renderer
{
public:
	Raycaster(Renderer& renderer);
	~Raycaster();

	void setArray(int arr[]);
	void loadArray();

	void const draw();
	void map2D();
	void const drawRays();
	void input(SDL_Event &event);



private:
	SDL_Event event;

	int mapX = 8, mapY = 8, mapSize = 64;

	float px, py;

	float playerAngle, dx, dy;

	float distT;
};
