#include <SDL.h>

import rpg.player;

namespace rpg::player
{
	Player::Player(RPG& rpg)
		: DynamicSprite(rpg, "player") {}

	void Player::useWeapon()
	{

	}

	void Player::onKeyDown(SDL_Keycode key)
	{
		switch (key)
		{
		case SDLK_a:
			this->setXDir(true);
			break;

		case SDLK_d:
			this->setXDir(false);
			break;
		}
	}

	void Player::onEvent(SDL_Event event)
	{
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == 1)
				this->useWeapon();
			break;
		}
	}

	void Player::onUpdate()
	{
		const Uint8* state = SDL_GetKeyboardState(nullptr);

		if (state[SDL_SCANCODE_W])
			this->setMotionY(this->getMotionY() - this->getSpeed());

		if (state[SDL_SCANCODE_S])
			this->setMotionY(this->getMotionY() + this->getSpeed());

		if (state[SDL_SCANCODE_A])
			this->setMotionX(this->getMotionX() - this->getSpeed());

		if (state[SDL_SCANCODE_D])
			this->setMotionX(this->getMotionX() + this->getSpeed());

		if (state[SDL_SCANCODE_R])
			this->dash();

		DynamicSprite::onUpdate();
	}
}