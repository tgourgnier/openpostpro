#include "mod_log.h"
#include <lang.h>
#include "logger.h"
#include "file.h"
#include "lang.h"
#include <imgui.h>

void ModLog::show(bool value)
{
	_show = config.display_log = value;
}

ModLog::ModLog(Window* window) : Module(window)
{
	_index = 2;
	_title = Lang::l("WINDOW_LOG");
	_last_modify = glfwGetTime();
	_code = "MOD_LOG";
	_show = config.display_log;
}

void ModLog::render_GUI()
{
	if ((glfwGetTime() - _last_modify) > 1.0) // pull every seconds
	{
		auto time = std::filesystem::last_write_time(std::filesystem::path(Logger::path()));
		if (time > _log_file_time)
		{
			_log_file_time = time;
			_buffer.clear();
			_lineOffsets.clear();
			auto lines = file::read_all_lines(Logger::path());
			if (lines.size() > 0)
			{
				_buffer.append(lines[0].c_str());
				_buffer.append("\n");
				for (int i = 1; i < lines.size(); i++)
				{
					_lineOffsets.push_back(_buffer.size());
					_buffer.append(lines[i].c_str());
					_buffer.append("\n");
				}
			}
			_scrollToBottom = true;
		}

		_last_modify = glfwGetTime();
	}

	ImGui::SetNextWindowSize(ImVec2(_width, _height));
	ImGui::SetNextWindowPos(ImVec2(_left, _top));
	ImGui::Begin("mouse_position", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

	if (ImGui::Button(Lang::l("CLEAR")))
	{
		Logger::clear();
		_lineOffsets.clear();
		_last_modify = 0;
	}

	ImGui::SameLine();
	_filter.Draw(Lang::l("FILTER"), -60.0f);
	ImGui::Separator();
	ImGui::BeginChild("scrolling");
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));

	if (_copy)
		ImGui::LogToClipboard();
	_copy = false;

	_window->push_default_font();

	if (_filter.IsActive())
	{
		const char* buf_begin = _buffer.begin();
		const char* line = buf_begin;
		for (int line_no = 0; line != NULL; line_no++)
		{
			const char* line_end = (line_no < _lineOffsets.Size) ? buf_begin + _lineOffsets[line_no] : NULL;
			if (_filter.PassFilter(line, line_end))
				ImGui::TextUnformatted(line, line_end);
			line = line_end && line_end[1] ? line_end + 1 : NULL;
		}
	}
	else
	{
		ImGui::TextUnformatted(_buffer.begin());
	}

	if (_scrollToBottom)
		ImGui::SetScrollHereY(1.0f);
	_scrollToBottom = false;
	_window->pop_font();
	ImGui::PopStyleVar();
	ImGui::EndChild();
	ImGui::End();

}