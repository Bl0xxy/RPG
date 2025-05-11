#include "map.hpp"

//inline const std::array<const std::string, 20> textureNames = {
//	"null",
//
//	//// GRASS ////
//	"grass_full",
//	"grass_raised_front", "grass_raised_back",
//	"grass_raised_left", "grass_raised_right",
//	"grass_raised_front_tall",
//
//	// Grass Bends
//	"grass_raised_corner_front_LEFT", "grass_raised_corner_front_RIGHT",
//	"grass_raised_corner_back_LEFT", "grass_raised_corner_back_RIGHT",
//
//	"grass_raised_front_elbow_left", "grass_raised_front_elbow_right",
//	"grass_raised_back_elbow_left", "grass_raised_back_elbow_right",
//
//	// DIRT
//	"dirt_full",
//	"dirt_end", "grass_dirt",
//
//	// CHARACTER SPRITES
//	"player", "player_back",
//};

int map[map_width][map_height] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 11, 2, 2, 2, 2, 2, 2, 2, 2, 12},
    {1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 4},
    {1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 4},
    {1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 4},
    {1, 1, 13, 3, 3, 3, 3, 3, 3, 3, 3, 14},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int mapWalls[map_width][map_height] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
