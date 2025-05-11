#include <algorithm>

import engine.sprite.follower;

constexpr int follower_speed = 4;

static int sign(int x)
{
	return (x > 0) - (x < 0);
}

namespace engine::sprite
{
	FollowerSprite::FollowerSprite(RPG& rpg, SDL_Texture* texture, BaseSprite* sprite = nullptr)
		: DynamicSprite(rpg, texture), followedSprite(sprite) {}

	FollowerSprite::FollowerSprite(RPG& rpg, const std::string& textureName, BaseSprite* sprite = nullptr)
		: DynamicSprite(rpg, textureName), followedSprite(sprite) {}

	FollowerSprite::FollowerSprite(RPG& rpg, int textureId, BaseSprite* sprite = nullptr)
		: DynamicSprite(rpg, textureId), followedSprite(sprite) {}

	void FollowerSprite::onUpdate()
	{
		DynamicSprite::onUpdate();

		if (!this->followedSprite)
			return;

		SDL_Rect target = this->followedSprite->getRect();
		Vector2 targetCenter = this->followedSprite->getCenter();

		int difX = this->getCenter().x - targetCenter.x;
		int difY = this->getCenter().y - targetCenter.y;

		int dx = std::abs(difX);
		int dy = std::abs(difY);

		int stepX = std::min(follower_speed, difX / follower_speed);
		int stepY = std::min(follower_speed, difY / follower_speed);

		if (dx < target.w / 2)
			this->setMotionX(this->getMotionX() * -1);

		if (dy < target.h / 2)
			this->setMotionY(this->getMotionY() * -1);

		if (dx > target.w * 2.25)
			this->setMotionX(this->getMotionX() - stepX);

		if (dy > target.h * 2.25)
			this->setMotionY(this->getMotionY() - stepY);
	}
}
