#pragma once

#include "module.h"
#include "window.h"
#include <filesystem>

class ModLog : public Module
{
private:
	ImGuiTextBuffer _buffer;
	ImGuiTextFilter _filter;
	ImVector<int> _lineOffsets;
	bool _scrollToBottom = false;
	bool _copy = false;
	std::filesystem::file_time_type _log_file_time;

	double _last_modify;
public:
	void show(bool value) override;

	ModLog(Window* window);
	void render_GUI() override;
};