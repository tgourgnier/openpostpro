#pragma once
#ifndef _MODOUTPUT_H
#define _MODOUTPUT_H

#include "module.h"
#include <filesystem>

#include "window.h"
#include <IMGUI_third/ImGuiColorTextEdit/TextEditor.h>

class ModOutput : public Module
{
private:
	std::filesystem::file_time_type _output_file_time;
	TextEditor editor;

	double _last_modify;
public:
	ModOutput(Window* window);

	void show(bool value) override;

	void document_loaded() override;

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