#pragma once
#include <string>
#ifndef _CLIPBOARD_H
#define _CLIPBOARD_H

class Clipboard
{
private:

#if !defined(_WIN32) && !defined(linux) && !defined(__linux) && defined(__MACH__)
	std::string _text = "";
#endif


public:
	static std::string text();
	static void text(std::string value);
};


#endif
