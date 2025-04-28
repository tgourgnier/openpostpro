#include "renderer.h"
#include "logger.h"
#include "environment.h"
#include <map>
#include <filesystem>
#include <exception>
#include "file.h"

Renderer::Renderer()
{
	_width = _height = 0;
}

Renderer::~Renderer()
{
}

void Renderer::initialize()
{
	load_programs();
}

void Renderer::load_programs()
{
	// load shaders from local shaders folder
	// vertex shader has '.vert' extension
	// fragment shadeer has '.frag' extension
	std::filesystem::path path(environment::application_path());
	path /= "shaders";

	std::map<std::string, std::filesystem::path> programs;

	if (std::filesystem::exists(path))
	{
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			if (entry.is_regular_file()) {
				int type = -1;
				auto extension = entry.path().extension().string();
				auto name = entry.path().filename().string();
				name = name.substr(0, name.size() - extension.size());

				programs[name] = entry;
			}

		}

		for (auto name : programs)
		{
			load_program(name.first, path.string());
		}
	}
}