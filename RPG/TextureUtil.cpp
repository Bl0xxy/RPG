#include "TextureUtil.hpp"
#include "Logger.hpp"
#include <SDL_image.h>

SDL_TexturePTR loadTexture(SDL_Renderer* renderer, SDL_Surface* surface)
{

	SDL_TexturePTR texture(SDL_CreateTextureFromSurface(renderer, surface),	SDL_DestroyTexture);

	if (!texture)
	{
		Logger::getLogger().error("Could not create texture from surface");
		return SDL_TexturePTR(nullptr, SDL_DestroyTexture);
	}

	return texture;
}

SDL_TexturePTR loadTexture(SDL_Renderer* renderer, const std::string& filename)
{
	SDL_SurfacePTR surface(IMG_Load(filename.c_str()), SDL_FreeSurface);

	if (!surface)
	{
		Logger::getLogger().error("Could not load asset \"" + filename + "\"");
		return SDL_TexturePTR(nullptr, SDL_DestroyTexture);
	}

	Logger::getLogger().info("Successfully loaded asset \"" + filename + "\"");
	return loadTexture(renderer, surface.get());
}