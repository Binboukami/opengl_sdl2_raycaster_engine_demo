#include <iostream>
#include "raycaster.h"

Raycaster::Raycaster(Renderer& renderer) : Renderer(renderer)
{
    px = 400, py = 300;
    dx = cos(playerAngle); dy = sin(playerAngle);
}
Raycaster::~Raycaster() {}

float dist(float ax, float ay, float bx, float by, float ang)
{
    return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

#pragma region Map Arrays

int map[64] = {};

int mapA[] =
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 1, 0, 1, 0, 1,
    1, 0, 1, 0, 0, 1, 0, 1,
    1, 0, 1, 0, 0, 1, 0, 1,
    1, 0, 1, 0, 1, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

int mapB[] =
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 1, 1, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 1, 1, 1, 0, 1,
    1, 0, 0, 0, 1, 0, 0, 1,
    1, 0, 0, 0, 1, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

int mapC[] =
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 1, 1, 0, 0, 1,
    1, 0, 0, 1, 1, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 1, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

#pragma endregion

#pragma region Array Functions

void Raycaster::setArray(int arr[])
{
    for (int i = 0; i < mapSize; i++)
    {
        map[i] = arr[i];
    }
}

void Raycaster::loadArray()
{
    setArray(mapA);
}

#pragma endregion

void const Raycaster::draw()
{
    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(px, py);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px, py);
    glVertex2i(px + dx * 5, py + dy * 5);
    glEnd();
}

void Raycaster::map2D()
{
    int x, y, xo, yo;
    for (y = 0; y < mapY; y++)
    {
        for (x = 0; x < mapX; x++)
        {
            if (map[y * mapX + x] == 1)
            {
                glColor3f(1, 1, 1);
            }
            if (map[y * mapX + x] == 0)
            {
                glColor3f(0.5, 0.5, 0.5);
            }
            xo = x * mapSize; yo = y * mapSize;

            glBegin(GL_QUADS);
            glVertex2i(xo + 1, yo + 1);
            glVertex2i(xo +1, yo + mapSize - 1);
            glVertex2i(xo + mapSize - 1, yo + mapSize - 1);
            glVertex2i(xo + mapSize - 1, yo + 1);
            glEnd();
        }
    }
}

void const Raycaster::drawRays()
{
    //call function to load the pre-loaded map array

    int r, mx, my, mapPos, depthField, fieldView;
    float rayAngle, rx, ry, xo, yo;

    rayAngle = playerAngle - DR * 30;
    fieldView = 60;

    if (rayAngle < 0) { rayAngle += 2 * PI; }
    if (rayAngle > 2 * PI) { rayAngle -= 2 * PI; }

    for (r = 0; r < fieldView ;r++)
    {
        //Check horizontal lines
        depthField = 0;
        float distH = 10000;
        float hx = px, hy = py;
        float aTan = -1 / tan(rayAngle);

        if (rayAngle > PI) { ry = (((int)py >> 6) << 6) - 0.0001; rx = (py - ry) * aTan + px; yo = -64; xo = -yo * aTan; }
        if (rayAngle < PI) { ry = (((int)py >> 6) << 6) + 64; rx = (py - ry) * aTan + px; yo = 64; xo = -yo * aTan; }
        if (rayAngle == 0 || rayAngle == PI) { rx = px; ry = py; depthField = 8; }

        while (depthField < 8)
        {
            mx = (int)(rx) >> 6; my = (int)(ry) >> 6; mapPos = my * mapX + mx;
            if (mapPos > 0 && mapPos < mapX * mapY && map[mapPos] == 1)
            {
                depthField = 8;
                hx = rx; hy = ry; distH = dist(px, py, hx, hy, rayAngle);
            }
            else
            {
                rx += xo; ry += yo;
                depthField += 1;
            }
            //glColor3f(0, 2, 0); glLineWidth(3); glBegin(GL_LINES); glVertex2i(px, py); glVertex2i(rx, ry); glEnd();
        }

        //Check vertical lines
        depthField = 0;
        float distV = 10000;
        float vx = px, vy = py;
        float nTan = -tan(rayAngle);

        if (rayAngle > P2 && rayAngle < P3) { rx = (((int)px >> 6) << 6) - 0.0001; ry = (px - rx) * nTan + py; xo = -64; yo = -xo * nTan; }
        if (rayAngle < P2 || rayAngle > P3) { rx = (((int)px >> 6) << 6) + 64; ry = (px - rx) * nTan + py; xo = 64; yo = -xo * nTan; }
        if (rayAngle == 0 || rayAngle == PI) { rx = px; ry = py; depthField = 8; }

        while (depthField < 8)
        {
            mx = (int)(rx) >> 6; my = (int)(ry) >> 6; mapPos = my * mapX + mx;
            if (mapPos > 0 && mapPos < mapX * mapY && map[mapPos] == 1)
            {
                depthField = 8;
                vx = rx; vy = ry; distV = dist(px, py, vx, vy, rayAngle);
            }
            else
            {
                rx += xo; ry += yo;
                depthField += 1;
            }
            //glColor3f(1, 0, 0); glLineWidth(2); glBegin(GL_LINES); glVertex2i(px, py); glVertex2i(rx, ry); glEnd();
        }

        if (distV < distH) { rx = vx; ry = vy; distT = distV; glColor3d(0.75, 0.7, 0.67); }
        if (distH < distV) { rx = hx; ry = hy; distT = distH; glColor3d(0.40, 0.4, 0.37); }

        rayAngle += DR;

        //fix fisheye;
        float cAngle = playerAngle - rayAngle;

        if (cAngle < 0) { cAngle += 2 * PI; }
        if (cAngle > 2 * PI) { cAngle -= 2 * PI; }

        distT = distT * cos(cAngle);

        //draw 3D Walls aaaaa
        float lineH = (mapSize * 300) / distT;
        if (lineH > 550) { lineH = 550; }

        float lineOffset = 300 - lineH / 2;

        glLineWidth(8);
        glBegin(GL_LINES);
        glVertex2i(r * 8 + 160, lineOffset); glVertex2i(r * 8 + 160, lineH + lineOffset);
        glEnd();


        if (rayAngle < 0) { rayAngle += 2 * PI; }
        if (rayAngle > 2 * PI) { rayAngle -= 2 * PI; }
    }
}


void Raycaster::input(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
#pragma region Player Controller Inputs
        case SDLK_w:
            px += dx; py += dy;
            break;
        case SDLK_s:
            px -= dx; py -= dy;
            break;
        case SDLK_a:
            playerAngle -= 0.1;
            if (playerAngle < 0)
            {
                playerAngle += 2 * PI;
            }
            dx = cos(playerAngle) * 5;	dy = sin(playerAngle) * 5;
            break;
        case SDLK_d:
            playerAngle += 0.1;
            if (playerAngle > 2 * PI)
            {
                playerAngle -= 2 * PI;
            }
            dx = cos(playerAngle) * 5;	dy = sin(playerAngle) * 5;
            break;
#pragma endregion

//obsolete
#pragma region Debug Control
        case SDLK_z:
            setArray(mapA);
            break;
        case SDLK_x:
            setArray(mapB);
            break;
        case SDLK_c:
            setArray(mapC);
#pragma endregion
        }
    }
}