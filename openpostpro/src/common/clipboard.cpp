#include "clipboard.h"


#if !defined(_WIN32) && !defined(linux) && !defined(__linux) && defined(__MACH__)

std::string Clipboard::text()
{
	return std::string();
}

void Clipboard::text(std::string value)
{
	_text = value;
}

#endif

#if defined(_WIN32)

#define _AMD64_

#include <windef.h>
#include <winuser.h>
#include <WinBase.h>

std::string Clipboard::text()
{
	std::string content = "";
	if (OpenClipboard(NULL))
	{
		auto handle = GetClipboardData(CF_TEXT);

		if (handle != NULL)
		{
			char* data = (char*)GlobalLock(handle);
			if (data != NULL)
			{
				content = data;
				GlobalUnlock(data);
			}
		}

		CloseClipboard();
	}

	return content;
}

void Clipboard::text(std::string value)
{
	if (OpenClipboard(NULL))
	{
		EmptyClipboard();

		HGLOBAL handle = GlobalAlloc(GMEM_MOVEABLE, (value.size() + 1) * sizeof(char));

		if (handle == NULL)
		{
			CloseClipboard();
			return;
		}

		char*  data = (char*)GlobalLock(handle);
		memcpy(data, value.c_str(), value.size() * sizeof(char));
		data[(value.size() + 1)] = 0;

		GlobalUnlock(data);

		SetClipboardData(CF_TEXT, handle);

		GlobalFree(handle);

		CloseClipboard();
	}
}

#endif
