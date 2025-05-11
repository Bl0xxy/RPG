#include "RPG.hpp"
#include <cmath>

import engine.render.camera;
import engine.sprite.dynamic;

constexpr float friction = 0.8;
constexpr float stop_speed = 0.05f;
constexpr float run_speed = 5.5f;
constexpr float dash_speed = 40.0f;
constexpr Uint32 dash_delay = 750;

static int sign(int x) {
	return (x > 0) - (x < 0);
}

static int sign(float x) {
	return (x > 0) - (x < 0);
}

static int sign(double x) {
	return (x > 0) - (x < 0);
}

namespace engine::sprite {
	DynamicSprite::DynamicSprite(RPG& rpg, SDL_Texture* texture)
		: BaseSprite(rpg, texture), motionX(0), motionY(0), speed(run_speed), lastTickDashed(SDL_GetTicks()), dashing(false), dashX(0), dashY(0), yDir(false), xDir(false)
	{
		this->setScale(5);
	}

	DynamicSprite::DynamicSprite(RPG& rpg, const std::string& textureName)
		: DynamicSprite(rpg, rpg.getTexture(textureName)) {}

	DynamicSprite::DynamicSprite(RPG& rpg, int textureId)
		: DynamicSprite(rpg, rpg.getTexture(textureId)) {}

	void DynamicSprite::onRender()
	{
		const auto* camera = this->rpg.getCamera();
		SDL_Rect rect = this->getRect();

		SDL_Rect dest = {
			static_cast<int>((rect.x - camera->x) * camera->zoom),
			static_cast<int>((rect.y - camera->y) * camera->zoom),
			static_cast<int>(rect.w * this->getScale() * camera->zoom),
			static_cast<int>(rect.h * this->getScale() * camera->zoom)
		};

		SDL_RenderCopyEx(this->rpg.getWindow().getRenderer(), this->getTexture(), nullptr, &dest, 0.0, nullptr, this->xDir ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	}

	void DynamicSprite::onUpdate()
	{
		int tileX = this->getRect().x / tile_size;
		int tileY = this->getRect().y / tile_size;

		float diagonalLength = std::sqrt(this->motionX * this->motionX + this->motionY * this->motionY);

		if (diagonalLength > this->speed) {
			this->motionX = (this->motionX / diagonalLength) * this->speed;
			this->motionY = (this->motionY / diagonalLength) * this->speed;
		}

		if (this->dashing)
		{
			this->motionX += this->dashX;
			this->motionY += this->dashY;
		}

		this->setX(this->getX() + this->motionX);
		this->setY(this->getY() + this->motionY);

		this->motionX *= friction;
		this->motionY *= friction;

		if (std::abs(this->motionX) < stop_speed)
			this->motionX = 0;

		if (std::abs(this->motionY) < stop_speed)
			this->motionY = 0;

		if (this->dashing && std::sqrt(std::pow(this->motionX, 2) + std::pow(this->motionY, 2) >= dash_speed))
			this->dashing = false;
	}

	void DynamicSprite::dash()
	{
		Uint32 tick = SDL_GetTicks();

		if (tick - this->lastTickDashed < dash_delay || this->dashing)
			return;

		this->lastTickDashed = tick;

		float diagonalSpeed = dash_speed / std::sqrt(2);

		this->dashX = 0;
		this->dashY = 0;

		if (this->motionX && this->motionY) {
			this->dashX = sign(this->motionX) * diagonalSpeed;
			this->dashY = sign(this->motionY) * diagonalSpeed;
		}
		else if (this->motionY)
			this->dashY = sign(this->motionY) * dash_speed;
		else if (this->motionX)
			this->dashX = sign(this->motionX) * dash_speed;
		else
			this->dashX = dash_speed;

		this->dashing = true;
	}
}