/*
 * main.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: naiello
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "ContentManager.h"
#include "WorldMap.h"

using namespace std;

#define SCREENW 640
#define SCREENH 480

int main(int argc, char** argv)
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "Failed to init SDL." << endl;
		return 1;
	}

	window = SDL_CreateWindow("Tilemap Loader", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREENW, SCREENH, SDL_WINDOW_SHOWN);

	if (!window)
	{
		cout << "Failed to open window." << endl;
		return 2;
	}

	IMG_Init(IMG_INIT_PNG);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	ContentManager content(renderer);
	WorldMap world("testmap.tmx", content);

	// Wait for user to press X button on window
	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		SDL_RenderClear(renderer);
		world.draw(renderer);
		SDL_RenderPresent(renderer);
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}
