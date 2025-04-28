#pragma once
#ifndef CAD_SCRIPT_H
#define CAD_SCRIPT_H

#include <string>
#include <vector>
#include <variant>
#include <document.h>
#include <script.h>

class CadScript : public Script
{
private:
	std::vector<std::variant<bool, int, float, std::string, std::vector<std::string>>> _properties;
	std::vector<std::variant<bool, int, float, std::string, std::vector<std::string>>> _properties_config;
	std::vector<std::string> _property_names;
	bool _first_call = true;

	// postpro python class
	PyObject* _py_script_module = nullptr;
	PyObject* _py_script_class = nullptr;
	PyObject* _py_script_object = nullptr;

private:
	void set_cadscript();

public:
	std::string category() { return _category; }
	std::string description() { return _description; }

	~CadScript();
	bool initialize(std::string module_path = "", std::string lang = "");
	void finalize();

	std::string run(glm::vec2 mouse_pos = glm::vec2(0,0));
};

#endif
