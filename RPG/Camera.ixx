export module engine.render.camera;

class RPG;

namespace engine::sprite {
	class BaseSprite;
}

export namespace engine::render
{
	struct Camera
	{
		int x, y;
		float zoom;
		engine::sprite::BaseSprite* follow;
		RPG& rpg;

		Camera(RPG& rpg, engine::sprite::BaseSprite* follow);
		void onUpdate();
	};
}
