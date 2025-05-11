#include "RPG.hpp"
#include <iostream>
#include <SDL_ttf.h>
#include <Logger.hpp>
#include <array>
#include <cmath>
#include "map.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>

import rpg.player;
import engine.render.camera;
import engine.scheduler;
import engine.sprite;

#define cdiv(a, b) (((a) + (b) - 1) / (b));

RPG::RPG() : window(), running(false), sprites(), player(nullptr), camera(nullptr), frameStart(SDL_GetTicks()), testEnemy(nullptr)
{
	if (this->window.getState() == -1)
	{
		std::cerr << "[CRITICAL] Window object failed to initialize!" << std::endl;
		return;
	}

	Logger::getLogger().info("RPG Window initialized");
	
	this->running = true;
	Logger::getLogger().info("RPG exited with code " + std::to_string(this->start()));
}

void RPG::initializeTextures()
{
	for (const std::string& name : textureNames)
		this->textures.emplace(name, loadTexture(this->window.getRenderer(), "assets/" + name + ".png"));
}

Window& RPG::getWindow()
{
	return this->window;
}

void RPG::drawTexture(SDL_Rect* dest, SDL_Texture* texture)
{
	if (!texture)
		return;

	SDL_RenderCopy(
		this->window.getRenderer(),
		texture,
		nullptr,
		dest
	);
}

SDL_Texture* RPG::getTexture(int textureId)
{
	SDL_Texture* out = this->getTexture(textureNames.at(textureId));
	return out;
}

SDL_Texture* RPG::getTexture(const std::string& textureName)
{
	SDL_Texture* out = this->textures.at(textureName).get();
	return out;
}

void RPG::onRender()
{
	SDL_SetRenderDrawColor(this->getWindow().getRenderer(), 12, 56, 103, 182);
	SDL_RenderClear(this->getWindow().getRenderer());

	// Draw Map
	int cameraX = this->camera->x;
	int cameraY = this->camera->y;
	int windowWidth, windowHeight;
	SDL_GetWindowSize(getWindow().getWindow(), &windowWidth, &windowHeight);

	float tileXf = static_cast<float>(cameraX) / static_cast<float>(tile_size_px);
	float tileYf = static_cast<float>(cameraY) / static_cast<float>(tile_size_px);

	int tileX = static_cast<int>(tileXf);
	int tileY = static_cast<int>(tileYf);

	int maxTileX = static_cast<int>(std::ceil(tileXf)) + cdiv(windowWidth, tile_size_px * camera->zoom);
	int maxTileY = static_cast<int>(std::ceil(tileYf)) + cdiv(windowHeight, tile_size_px * camera->zoom);

	for (int col = tileX; col < maxTileX; col++)
	{
		if (col >= map_width || col < 0)
			continue;

		for (int row = tileY; row < maxTileY; row++)
		{
			if (row >= map_height || row < 0)
				continue;

			SDL_Rect dest = {
				static_cast<int>((col * tile_size_px - cameraX) * camera->zoom),
				static_cast<int>((row * tile_size_px - cameraY) * camera->zoom),
				static_cast<int>(tile_size_px * camera->zoom),
				static_cast<int>(tile_size_px * camera->zoom)
			};

			int textureId = map[row][col];

			if (textureId < 0 || textureId >= textureNames.size())
				textureId = 0;

			const std::string& textureName = textureNames.at(textureId);

			SDL_Texture* texture = this->textures.at(textureName).get();
			this->drawTexture(&dest, texture);
		}
	}

	// Draw Sprites
	std::vector<engine::sprite::BaseSprite*> drawQueue;
	for (std::unique_ptr<Sprite>& sprite : this->sprites)
		drawQueue.push_back(sprite.get());

	std::sort(drawQueue.begin(), drawQueue.end(),
		[](const Sprite* a, const Sprite* b) {
			return a->getRect().y + a->getRect().h < b->getRect().y + b->getRect().h;
		}
	);

	for (Sprite* sprite : drawQueue)
		sprite->onRender();
	
	// Draw Text
	float xValue = static_cast<float>(this->player->getScaledRect().x) / static_cast<float>(tile_size_px);
	float yValue = static_cast<float>(this->player->getScaledRect().y) / static_cast<float>(tile_size_px);

	std::ostringstream ossX, ossY;
	ossX << std::fixed << std::setprecision(1) << xValue;
	ossY << std::fixed << std::setprecision(1) << yValue;

	this->window.renderText("X: " + ossX.str());
	this->window.renderText("Y: " + ossY.str(), 0, 30);

	SDL_RenderPresent(this->getWindow().getRenderer());
}

void RPG::onUpdate()
{
	for (std::unique_ptr<Sprite>& sprite : this->sprites)
		sprite->onUpdate();
	this->camera->onUpdate();
}

void RPG::onKeyDown(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_i:
		this->camera->zoom *= 2;
		break;

	case SDLK_o:
		this->camera->zoom /= 2;
		break;

	case SDLK_n:
		this->camera->follow = this->sprites.at(0).get();
		break;

	case SDLK_m:
		this->camera->follow = this->player;
		break;

	case SDLK_t:
		this->testEnemy->setFollowedSprite(this->player);
		break;

	case SDLK_y:
		this->testEnemy->setFollowedSprite(nullptr);
		break;
	}

	for (std::unique_ptr<Sprite>& sprite : this->sprites)
		sprite->onKeyDown(key);
}

void RPG::onEvent(SDL_Event event)
{
	switch (event.type)
	{
	case SDL_QUIT:
		this->running = false;
		Logger::getLogger().info("SDL_Quit event has been called! Exiting...");
		break;

	case SDL_KEYDOWN:
		this->onKeyDown(event.key.keysym.sym);
		break;

	default:
		break;
	}
}

int RPG::start()
{
	this->initializeTextures();

	camera = std::make_unique<engine::render::Camera>(*this);

	auto usprite = std::make_unique<engine::sprite::BaseSprite>(*this, "player");
	usprite->setScale(render_scale);
	this->sprites.push_back(std::move(usprite));

	auto uenemy = std::make_unique<engine::sprite::FollowerSprite>(*this, "player");
	this->testEnemy = uenemy.get();
	this->sprites.push_back(std::move(uenemy));

	auto uplayer = std::make_unique<rpg::player::Player>(*this);
	this->player = uplayer.get();
	this->sprites.push_back(std::move(uplayer));

	this->camera->follow = this->player;

	int frameTime;

	while (this->running)
	{
		this->frameStart = SDL_GetTicks();

		SDL_Event event;
		while (SDL_PollEvent(&event))
			onEvent(event);

		if (!this->running)
			break;

		this->onUpdate();
		this->onRender();

		frameTime = SDL_GetTicks() - this->frameStart;

		if (frame_delay > frameTime)
			SDL_Delay(frame_delay - frameTime);
	}

	return 0;
}

const engine::render::Camera* RPG::getCamera() const
{
	return this->camera.get();
}
