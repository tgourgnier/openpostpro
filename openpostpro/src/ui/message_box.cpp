#include "message_box.h"
#include <lang.h>
#include <strings.h>

std::string MessageBox::result()
{
	return _result;
}

void MessageBox::input(std::string title, std::string text, std::string value, MessageBoxButtons buttons)
{
	_enabled = true;
	_text = text;
	_title = title;
	if (value != "")
		_result = value;
	_input = true;
	_buttons = buttons;
}

void MessageBox::display(std::string title, std::string text, MessageBoxButtons buttons)
{
	_enabled = true;
	_text = text;
	_title = title;
	_input = false;
	_buttons = buttons;
}

MessageBoxStatus MessageBox::show()
{
	MessageBoxStatus result = MessageBoxStatus::None;
	if (_enabled)
	{
		char input[20];
		sprintf_s(input, _result.c_str());

		auto lines_count = stringex::split(_text, '\n').size();

		ImGuiIO& io = ImGui::GetIO();
		ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::SetNextWindowSize(ImVec2(300.0f, (_input ? 90.0f : 60.0f) + lines_count * 20.0f));
		ImGui::Begin(_title.c_str(), 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
		auto windowWidth = ImGui::GetWindowSize().x;
		auto textWidth = ImGui::CalcTextSize(_text.c_str()).x;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
		ImGui::Text(_text.c_str());
		ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x - ImGui::CalcItemWidth()) / 2.f);
		if (_input && ImGui::InputText("##INPUT_MESSAGE_BOX", input, 20 * sizeof(char)))
		{
			_result = input;
		}
		ImGui::NewLine();
		ImGuiStyle& style = ImGui::GetStyle();
		windowWidth = ImGui::GetWindowSize().x;
		textWidth = ImGui::CalcTextSize(Lang::l("BTN_OK")).x;
		if (_buttons == MessageBoxButtons::OkCancel)
			textWidth += ImGui::CalcTextSize(Lang::l("BTN_CANCEL")).x;
		if (_buttons == MessageBoxButtons::YesNo)
			textWidth = ImGui::CalcTextSize(Lang::l("BTN_YES")).x + ImGui::CalcTextSize(Lang::l("BTN_NO")).x;

		ImGui::SetCursorPosX((windowWidth - (textWidth + style.ItemSpacing.x)) * 0.5f);
		if (_buttons == MessageBoxButtons::Ok || _buttons == MessageBoxButtons::OkCancel)
		{
			if (ImGui::Button(Lang::l("BTN_OK")))
			{
				_enabled = false;
				result = MessageBoxStatus::Ok;
			}
		}
		if (_buttons == MessageBoxButtons::OkCancel)
		{
			ImGui::SameLine();
			if (_input && ImGui::Button(Lang::l("BTN_CANCEL")))
			{
				_enabled = false;
				result = MessageBoxStatus::Cancel;
			}
		}
		if (_buttons == MessageBoxButtons::YesNo)
		{
			if (ImGui::Button(Lang::l("BTN_YES")))
			{
				_enabled = false;
				result = MessageBoxStatus::Yes;
			}
			ImGui::SameLine();
			if (ImGui::Button(Lang::l("BTN_NO")))
			{
				_enabled = false;
				result = MessageBoxStatus::No;
			}
		}
		ImGui::End();
	}

	return result;
}