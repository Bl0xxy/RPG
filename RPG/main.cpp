#include <SDL.h>
#include <iostream>
#include "RPG.hpp"
#include <direct.h>
#include "Logger.hpp"

int main(int argc, char* argv[])
{
	std::string basePath = SDL_GetBasePath();

	if (_chdir((basePath + "/onpath").c_str()))
	{
		Logger::getLogger().error("Cannot find executable folder");
		return -1;
	}

	try { RPG rpg; }
	catch (const std::exception& e) {Logger::getLogger().critical("Game crashed with exception \"" + std::string(e.what()) + "\""); }
	return 0;
}