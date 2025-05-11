#pragma once

#include <SDL.h>
import std;

struct Vector2
{
	int x, y;
};

using SDL_TexturePTR = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>;
using SDL_SurfacePTR = std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)>;

SDL_TexturePTR loadTexture(SDL_Renderer* renderer, SDL_Surface* surface);
SDL_TexturePTR loadTexture(SDL_Renderer* renderer, const std::string& filename);
