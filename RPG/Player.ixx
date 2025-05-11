export module rpg.player;

#include <SDL.h>


import engine.sprite.dynamic;

class RPG;

export namespace rpg::player
{
	class Player
		: public engine::sprite::DynamicSprite
	{
	private:
		void useWeapon();

	public:
		Player(RPG& rpg);

		void onUpdate() override;
		void onEvent(SDL_Event event) override;
		void onKeyDown(SDL_Keycode key) override {}
	};
}
