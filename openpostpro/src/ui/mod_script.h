#pragma once

#ifndef _MODSCRIPT_H
#define _MODSCRIPT_H

#include "module.h"
#include <filesystem>

#include "window.h"
#include <IMGUI_third/ImGuiColorTextEdit/TextEditor.h>

class ModScript : public Module
{
private:
	std::filesystem::file_time_type _output_file_time;
	TextEditor editor;

	double _last_modify;
	bool _modified = false;
	std::string _path;
	std::string _data;

public:
	bool modified() { return _modified; }
	std::string path() { return _path; }
	std::string data() { return _data; }

	ModScript(Window* window);

	void document_loaded() override;

	void load(std::string path) override;
	void unload() override;

	// undo/redo
	void undo() override;
	void redo() override;
	void clear_history() override;
	bool can_undo() override;
	bool can_redo() override;

	// selection
	void select_all() override;
	void unselect_all() override;

	// clipboard
	void cut() override;
	void copy() override;
	void paste() override;
	void remove() override;

	void render_GUI() override;
};

#endif