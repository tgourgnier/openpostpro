#pragma once
#include <vector>
#include <algorithm>
#include "window.h"
#include "renderer.h"
#include <inifile.h>

enum class MessageBoxResult
{
	None,
	Ok,
	Cancel
};

class Config
{
private:
	IniFile _ini;
	std::string _section = "GENERAL";
	IniFile _ini_temp;
	bool _load_temp = true;


	void load_colors();

public:
	std::vector<std::string> file_history;

	bool first = true;
	int display_style = 1;
	bool open_last_file = true;
	std::string last_file_path = "";
	bool small_axe = false;
	bool use_grid = false;
	float inc_grid = 10;
	bool show_decoration = false;
	bool show_point_as_cross = false;
	bool show_cam_arrow = true;
	bool show_cam_start = true;
	std::string postpro = "";
	std::string output_path = "";

	bool display_log = false;
	bool display_output = false;

	std::string python_path = "";

	Config();


	glm::vec4 anchorFillColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f);
	glm::vec4 anchorLineColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 anchorOverFillColor = glm::vec4(0.0f, 1.0f, 0.0f, 0.5f);
	glm::vec4 anchorOverLineColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	glm::vec4 decorationColor = glm::vec4(0.871f, 0.871f, 0.871f, 0.5f);
	glm::vec4 mouseOverColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	glm::vec4 axeColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 gridColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f);
	glm::vec4 background2DColor = glm::vec4(0.25f, 0.25f, 0.25f, 0.0f);
	glm::vec4 layerColor = glm::vec4(0.278f, 0.78f, 1.0f, 1.0f);
	glm::vec4 groupColor = glm::vec4(0.173f, 0.271f, 0.631f, 1.0f);
	glm::vec4 selectedCadColor = glm::vec4(0.0f, 0.8f, 0.0f, 1.0f);
	glm::vec4 selectedCamColor = glm::vec4(1.0f, 1.1f, 1.0f, 1.0f);

	std::map<std::string, glm::vec4> colors;
	std::vector<std::string> dxfColorNames;
	std::vector<std::string> colorNames;
	std::vector<std::string> vividColorNames;

	// debug
	bool field_space_toggled = false;
	bool field_f1_toggled = false;
	bool field_f2_toggled = false;
	bool field_f3_toggled = false;
	bool field_f4_toggled = false;
	bool field_f5_toggled = false;
	bool field_f6_toggled = false;
	bool field_f7_toggled = false;
	bool field_f8_toggled = false;
	bool field_f9_toggled = false;
	// end debug

	// internal autosave state field
	float chamfer_radius = 1.0f;

	void read();
	void write();

	MessageBoxResult drawUI();
};

extern Config config;
