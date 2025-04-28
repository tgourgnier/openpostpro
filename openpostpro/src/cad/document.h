#pragma once
#include <string>
#include "graphic.h"
#include <vector>
#include <layer.h>
#include <group.h>

enum doc_type {
	router
};

class Document
{
private:
	std::string _path;						// file path
	std::string _output;					// file output
	std::vector<Layer*> _layers;			// store layers
	std::vector<Group*> _groups;			// store groups
	doc_type _type = doc_type::router;		// type of document
	Renderer* _render = nullptr;			// rendering device	
	std::vector<Graphic*> _selected;		// store actual selected graphics elements
	std::vector<Graphic*> _references;		// store actual graphics elements used as references
	Layer* _current_layer = nullptr;		// current selected layer
	Group* _current_group = nullptr;		// current selected group
	bool _modified = false;

	float _scale = 1.0f;					// last camera scale factor

public:
	Document();
	~Document();

	Renderer* render() { return _render; }
	void render(Renderer* r) { _render = r; reset(); }

	doc_type type() { return _type; }
	void type(doc_type value) { _type = value; }

	std::string path() { return _path; }
	void path(std::string value) { _path = value; }

	std::string output() { return _output; }
	void output(std::string value) { _output = value; }

	bool modified() { return _modified; }
	void modified(bool value) { _modified = value; }

	std::vector<Layer*>& layers() { return _layers; }
	Layer* layer(std::string name="");

	std::vector<Group*>& groups() { return _groups; }
	Group* group(std::string name="");

	std::vector<Graphic*>& selected() { return _selected; }

	Layer* current_layer() { return _current_layer; }
	void current_layer(Layer* value) { _current_layer = value; }
	
	Group* current_group() { return _current_group; }
	void current_group(Group* value) { _current_group = value; }

	/// <summary>
	/// Return the coordinates from a reference shape and all the other connected shapes
	/// </summary>
	/// <param name="r">shape to start from</param>
	/// <returns>coordinates</returns>
	std::vector<glm::vec2> reference(Shape* r);

	void remove_layer(Layer* value);
	void remove_layer(std::string name);
	void remove_group(Group* value);
	void remove_group(std::string name);

	void up(Graphic* g);
	void down(Graphic* g);

	void select_all();
	void unselect_all();
	void select(Graphic* g);
	void select(std::vector<Graphic*> list);
	void unselect(Graphic* g);
	void unselect(std::vector<Graphic*> list);

	void reset();
	void draw();
	void anchors();
	void clear();
	void init();
	void check();

	// IO
	std::string write(float version = 0);
	void read(std::string value);
};