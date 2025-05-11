export module engine.sprite.base;

#include <SDL.h>
#include "TextureUtil.hpp"

class RPG;

export namespace engine::sprite
{
	class BaseSprite
	{
	private:
		SDL_Texture* texture;
		SDL_Rect rect;
		int scale;

	protected:
		RPG& rpg;

		void setX(int value)
		{
			this->rect.x = value;
		}

		void setY(int value)
		{
			this->rect.y = value;
		}

	public:
		BaseSprite(RPG& rpg, SDL_Texture* texture);
		BaseSprite(RPG& rpg, const std::string& textureName);
		BaseSprite(RPG& rpg, int textureId);

		virtual void onRender();
		virtual void onUpdate() {}
		virtual void onKeyDown(SDL_Keycode key) {}
		virtual void onEvent(SDL_Event event) {}

		int getScale() const
		{
			return this->scale;
		}

		void setScale(int scale)
		{
			this->scale = scale;
		}

		int getWidth() const
		{
			return this->rect.w;
		}

		int getHeight() const
		{
			return this->rect.h;
		}

		int getX() const
		{
			return this->rect.x;
		}

		int getY() const
		{
			return this->rect.y;
		}

		int getScaledWidth() const
		{
			return this->rect.w * this->scale;
		}

		int getScaledHeight() const
		{
			return this->rect.h * this->scale;
		}

		int getScaledX() const
		{
			return this->rect.x * this->scale;
		}

		int getScaledY() const
		{
			return this->rect.y * this->scale;
		}

		SDL_Rect getRect() const
		{
			return this->rect;
		}

		SDL_Rect getScaledRect() const
		{
			return { getScaledX(), getScaledY(), getScaledWidth(), getScaledHeight() };
		}

		Vector2 getCenter() const
		{
			return {
				this->rect.x + this->rect.w / 2,
				this->rect.y + this->rect.h / 2
			};
		}

		SDL_Texture* getTexture() const
		{
			return this->texture;
		}
	};
}