#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include <string>

using SDL_WindowPTR = std::unique_ptr<SDL_Window, void(*)(SDL_Window*)>;
using SDL_RendererPTR = std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)>;
using TTF_FontPTR = std::unique_ptr<TTF_Font, void(*)(TTF_Font*)>;

class Window
{
private:
	SDL_WindowPTR window;
	SDL_RendererPTR renderer;
	TTF_FontPTR font;

	int state;

public:
	Window();
	~Window();

	int getState() const;
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	void renderText(const std::string& text, int x = 0, int y = 0, SDL_Color color = {255, 255, 255, 255});
};
