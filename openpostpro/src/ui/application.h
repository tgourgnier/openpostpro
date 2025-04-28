#pragma once
#include "window.h"
#include "lang.h"
#include <imgui.h>
#include "module.h"
#include <renderer_opengl.h>
#include <mutex>
#include <postpro.h>
#include <vector>
#include <cad_script.h>

class Application :
	public Window
{
private:
	float _version = 0.1f;

	int _xpos = 0;
	int _ypos = 0;
	int _menu_height = 0;
	std::vector<Module*> _modules;
	Module* _current_module = NULL;
	float _nav_width = 56.0f;

	int _nav_style = 0;

	ImFont* _font = NULL;

	Document* _document = NULL;

	std::mutex _mutex;
	std::mutex _move_mutex;
	bool _initialized = false;
	std::string _imgui_ini;

	glm::vec2 _top_left = glm::vec2();
	glm::vec2 _bottom_right = glm::vec2();

	bool _display_preferences = false;
	bool _display_postpro_preferences = false;

	std::string _application_title = "";

	std::vector<Postpro*> _postpros;
	Postpro* _current_postpro = nullptr;

	std::vector<CadScript*> _scripts;

public:
	Application(std::string title);
	~Application();

	void initialize() override;
	void finalize() override;

	void onSizeChanged(float width, float height) override;
	void onMouseMove(double xpos, double ypos) override;
	void onLeftButtonDown() override;
	void onLeftButtonUp() override;
	void onRightButtonDown() override;
	void onRightButtonUp() override;
	void onScroll(double xoffset, double yoffset) override;
	void onEnter() override;
	void onLeave() override;
	void onKeyPressed(int key, int scancode, int action, int mods) override;
	void onCharacterInput(unsigned int codepoint) override;
	void onDrop(std::vector<std::string> paths) override;
	void onRenderFrame() override;
	void onRenderGUI() override;

	void render_menu();

	void new_document();
	void load_file(std::string path);
	void save_file(std::string path);
	void load_dxf(std::string path);

	Module* module(std::string code);

	void insert(std::string content);
};

