#include "Window.hpp"
#include <Logger.hpp>
#include "TextureUtil.hpp"
#include <SDL_image.h>

int Window::getState() const
{
	return this->state;
}

Window::Window()
	: window(nullptr, SDL_DestroyWindow), renderer(nullptr, SDL_DestroyRenderer), font(nullptr, TTF_CloseFont), state(0)
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Logger::getLogger().critical("SDL could not initialize: " + std::string(SDL_GetError()));
		this->state = -1;
		return;
	}
	Logger::getLogger().info("SDL initialized");

	if (TTF_Init() == -1)
	{
		Logger::getLogger().critical("SDL_ttf could not initialize: " + std::string(TTF_GetError()));
		this->state = -1;
		return;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		Logger::getLogger().critical("SDL_image could not initialize: " + std::string(IMG_GetError()));
		this->state - -1;
		return;
	}

	Logger::getLogger().info("SDL_ttf initialized");

	this->font.reset(TTF_OpenFont("font.ttf", 24));

	if (!this->font)
	{
		Logger::getLogger().critical("Font could not be created: " + std::string(TTF_GetError()));
		this->state = -1;
		return;
	}

	this->window.reset(SDL_CreateWindow(
		"My RPG",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		800, 600,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED
	));

	if (!this->window)
	{
		Logger::getLogger().critical("Window could not be created: " + std::string(SDL_GetError()));
		this->state = -1;
		return;
	}
	Logger::getLogger().info("SDL_Window initialized");

	renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));
	if (!this->renderer)
	{
		Logger::getLogger().critical("Renderer could not be created: " + std::string(SDL_GetError()));
		this->state = -1;
		return;
	}
	Logger::getLogger().info("SDL_Renderer initialized");
}

Window::~Window()
{
	SDL_Quit();
}

SDL_Window* Window::getWindow()
{
	return this->window.get();
}

SDL_Renderer* Window::getRenderer()
{
	return this->renderer.get();
}

void Window::renderText(const std::string& text, int x, int y, SDL_Color color)
{
	SDL_SurfacePTR surface(TTF_RenderText_Solid(this->font.get(), text.c_str(), color), SDL_FreeSurface);
	SDL_TexturePTR texture(SDL_CreateTextureFromSurface(this->renderer.get(), surface.get()), SDL_DestroyTexture);

	int w = surface->w,
		h = surface->h;

	SDL_Rect quad = { x, y, w, h };
	SDL_RenderCopy(this->renderer.get(), texture.get(), nullptr, &quad);
}