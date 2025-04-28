#pragma once
#ifndef _MESSAGE_BOX_H
#define _MESSAGE_BOX_H

#include <imgui.h>
#include <string>

enum class MessageBoxStatus
{
	None,
	Ok,
	Cancel,
	Yes,
	No
};

enum class MessageBoxButtons
{
	Ok,
	OkCancel,
	YesNo
};

class MessageBox
{
private:
	bool _enabled=false;
	bool _input=false;

	std::string _title;
	std::string _text;
	std::string _result;

	MessageBoxButtons _buttons = MessageBoxButtons::Ok;

public:
	std::string result();

	void input(std::string title, std::string text, std::string value = "", MessageBoxButtons buttons = MessageBoxButtons::Ok);
	void display(std::string title, std::string text, MessageBoxButtons buttons = MessageBoxButtons::Ok);
	MessageBoxStatus show();
};

#endif