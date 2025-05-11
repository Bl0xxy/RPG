#include "RPG.hpp"

import engine.sprite.base;
import engine.render.camera;

namespace engine::sprite
{
	BaseSprite::BaseSprite(RPG& rpg, SDL_Texture* texture)
		: texture(texture), rpg(rpg), rect({ 0, 0, 0, 0 }), scale(1)
	{
		SDL_QueryTexture(this->texture, nullptr, nullptr, &this->rect.w, &this->rect.h);
	}

	BaseSprite::BaseSprite(RPG& rpg, const std::string& textureName)
		: BaseSprite(rpg, rpg.getTexture(textureName)) {}

	BaseSprite::BaseSprite(RPG& rpg, int textureId)
		: BaseSprite(rpg, rpg.getTexture(textureId)) {}

	void BaseSprite::onRender()
	{
		const auto* camera = this->rpg.getCamera();
		SDL_Rect dest = {
			static_cast<int>((this->rect.x - camera->x) * camera->zoom),
			static_cast<int>((this->rect.y - camera->y) * camera->zoom),
			static_cast<int>(this->rect.w * this->scale * camera->zoom),
			static_cast<int>(this->rect.h * this->scale * camera->zoom)
		};

		SDL_RenderCopy(this->rpg.getWindow().getRenderer(), this->texture, nullptr, &dest);
	}
}
