#pragma once

#include "Window.hpp"
#include "TextureUtil.hpp"
#include <vector>
#include <string>
#include <map>
#include <array>

namespace rpg::player {
	class Player;
}

namespace engine {
	namespace sprite {
		class BaseSprite;
		class FollowerSprite;
	}

	namespace render {
		class Camera;
	}
}

constexpr int render_scale = 6;
constexpr int tile_size = 16;
constexpr int tile_size_px = tile_size * render_scale;
constexpr int FPS = 60;
constexpr int frame_delay = 1000 / FPS;

inline const std::array<const std::string, 20> textureNames = {
	"null",

	//// GRASS ////
	"grass_full",
	"grass_raised_front", "grass_raised_back", 
	"grass_raised_left", "grass_raised_right", 
	"grass_raised_front_tall",

	// Grass Bends
	"grass_raised_corner_front_LEFT", "grass_raised_corner_front_RIGHT",
	"grass_raised_corner_back_LEFT", "grass_raised_corner_back_RIGHT",

	"grass_raised_front_elbow_left", "grass_raised_front_elbow_right",
	"grass_raised_back_elbow_left", "grass_raised_back_elbow_right",

	// DIRT
	"dirt_full",
	"dirt_end", "grass_dirt",

	// CHARACTER SPRITES
	"player", "player_back",
};

class RPG
{
private:
	Window window;
	bool running;
	rpg::player::Player* player;
	engine::sprite::FollowerSprite* testEnemy;
	std::unique_ptr<engine::render::Camera> camera;
	std::vector<std::unique_ptr<engine::sprite::BaseSprite>> sprites;
	std::map<const std::string, SDL_TexturePTR> textures;
	Uint32 frameStart;

	int start();
	void onRender();
	void onUpdate();
	void onEvent(SDL_Event event);
	void onKeyDown(SDL_Keycode key);
	void initializeTextures();
	void drawTexture(SDL_Rect* dest, SDL_Texture* texture);

public:
	RPG();
	Window& getWindow();
	const engine::render::Camera* getCamera() const;
	SDL_Texture* getTexture(const std::string& textureName);
	SDL_Texture* getTexture(int textureId);

};

