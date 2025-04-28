/******************************************************************
* OpenPostPro - www.openpostpro.org
* ------------------------------------------------------------------------
* Copyright(c) 2024 Thomas Gourgnier
*
* This software is provided 'as-is', without any express or implied
* warranty.In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions :
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software.If you use this software
*    in a product, an acknowledgment in the product documentation would
*    be appreciated but is not required.
*
* 2. Altered source versions must be plainly marked as such, and must not
*    be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source
*    distribution.
*
*************************************************************************/

/************************************************************************
* Register history events
*************************************************************************/
#pragma once
#ifndef _HISTORY_H
#define _HISTORY_H

#include <string>
#include <mutex>
#include <vector>

enum class HistoryActionType
{
	Delete,
	Add,
	Modify,
	BeginRecord,
	EndRecord,
	None
};

struct HistoryAction
{
	HistoryActionType type = HistoryActionType::None;
	std::string value = "";

	HistoryAction()
	{
		type = HistoryActionType::Add;
		value = "";
	}

	HistoryAction(HistoryActionType type, std::string value)
	{
		this->type = type;
		this->value = value;
	}

	HistoryAction& operator=(HistoryAction& right)
	{
		type = right.type;
		value = right.value;
		return *this;
	}

	HistoryAction& operator=(HistoryAction right)
	{
		type = right.type;
		value = right.value;
		return *this;
	}
};

class History
{
private:
	static std::mutex _mutex;
	static std::vector<HistoryAction> _undo;
	static std::vector<HistoryAction> _redo;

public:
	static bool has_undo();

	static bool has_redo();

	static size_t undo_count();

	static size_t redo_count();

	/// <summary>
	/// push undo action
	/// </summary>
	static void undo(HistoryActionType type, std::string value, bool clear_redo = true);

	/// <summary>
	/// push undo action
	/// </summary>
	static void undo(HistoryAction action, bool clear_redo=true);

	/// <summary>
	/// push redo action
	/// </summary>
	static void redo(HistoryActionType type, std::string value);

	/// <summary>
	/// push redo action
	/// </summary>
	static void redo(HistoryAction action);

	/// <summary>
	/// start multiple HistoryActionType to be processed
	/// </summary>
	static void begin_undo_record(bool clear_redo = true);

	/// <summary>
	/// end multiple HistoryActionType to be processed
	/// </summary>
	static void end_undo_record(bool clear_redo = true);

	/// <summary>
	/// start multiple HistoryActionType to be processed
	/// </summary>
	static void begin_redo_record();

	/// <summary>
	/// end multiple HistoryActionType to be processed
	/// </summary>
	static void end_redo_record();

	/// <summary>
	/// pop undo action
	/// </summary>
	static HistoryAction undo();

	/// <summary>
	/// pop redo action
	/// </summary>
	static HistoryAction redo();

	/// <summary>
	/// Clear history file
	/// </summary>
	static void clear();
};

#endif