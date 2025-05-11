#include <SDL.h>
#include "RPG.hpp"

import engine.render.camera;
import engine.sprite.base;

constexpr float stop_distance = 2.0f;
constexpr int camera_speed = 4;

namespace engine::render
{
	Camera::Camera(RPG& rpg, engine::sprite::BaseSprite* follow)
		: x(0), y(0), zoom(1.0f), rpg(rpg), follow(follow) {}

	void Camera::onUpdate()
	{
		if (!follow)
			return;

		int ww, wh;
		SDL_GetWindowSize(this->rpg.getWindow().getWindow(), &ww, &wh);

		int nx = static_cast<int>((static_cast<float>(follow->getScaledX()) * this->zoom + static_cast<float>(follow->getScaledWidth()) / 2 * this->zoom - ww / 2) / this->zoom);
		int ny = static_cast<int>((static_cast<float>(follow->getScaledY() * this->zoom + static_cast<float>(follow->getScaledHeight()) / 2 * this->zoom - wh / 2) / this->zoom);

		int dx = this->x - nx;
		int dy = this->y - ny;

		this->x -= dx / camera_speed;
		this->y -= dy / camera_speed;
	}
}