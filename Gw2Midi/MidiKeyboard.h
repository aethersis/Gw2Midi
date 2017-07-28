#pragma once
#include <Windows.h>
#include <cstdint>
#include <exception>

#define OCTAVE_UP '0'
#define OCTAVE_DOWN '9'

class MidiKeyboard
{
public:
	void processMidiKey(DWORD midiEvent)
	{
		bool noteOn = false;
		m_currentKey = eventToNoteId(midiEvent, noteOn);

		if (noteOn)
		{
			auto octave = noteToOctave(m_currentKey);

			emitNewOctave(m_currentOctave, octave);
			m_currentOctave = octave;
			emitKeyPress(noteToKey(m_currentKey));
		}
	}

private:
	uint8_t eventToNoteId(DWORD midiEvent, bool& success)
	{
		bool noteOn = ((midiEvent & 0x000000ff) == 0x00000090);
		auto note = (midiEvent & 0x0000ff00) >> 8;

		success = noteOn;

		if (success)
		{
			std::cout << "Received noteId: " << note << "\n";
		}

		return note;
	}

	int8_t noteToOctave(uint8_t noteId)
	{
		const uint8_t semitonesInOctave = 12;
		return noteId / semitonesInOctave;
	}

	char noteToKey(uint8_t note)
	{
		uint8_t noteFromZero = note % 12;

		switch (noteFromZero)
		{
		case 0:
			return '1';
		case 1:
			return '1';
		case 2:
			return '2';
		case 3:
			return '2';
		case 4:
			return '3';
		case 5:
			return '4';
		case 6:
			return '4';
		case 7:
			return '5';
		case 8:
			return '5';
		case 9:
			return '6';
		case 10:
			return '6';
		case 11:
			return '7';
		}

		// this should never happen
		return '1';
	}

	void emitKeyPress(char key)
	{
		INPUT input;
		memset(&input, 0, sizeof(INPUT));
		input.type = INPUT_KEYBOARD;

		if (key == OCTAVE_UP) //octave up
		{
			input.ki.wScan = 0x040B;
		}
		else if (key == OCTAVE_DOWN) //octave down
		{
			input.ki.wScan = 0x040A;
		}
		else if (key > '0' && key < '9') //note
		{
			input.ki.wScan = 0x0401 + key - '0';
		}

		input.ki.dwFlags = 0;
		SendInput(1, &input, sizeof(INPUT));
		input.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &input, sizeof(INPUT));

		//SendMessage(m_windowHandle, WM_KEYDOWN, VK_LSHIFT, NULL); // push key
		//Sleep(10); // hold key. not always works without this.
		//SendMessage(m_windowHandle, WM_KEYUP, VK_LSHIFT, NULL); // release key
	}

	void emitNewOctave(uint8_t currentOctave, uint8_t newOctave)
	{
		int octaveDifference = newOctave - currentOctave;
		char octaveKey = octaveDifference > 0 ? OCTAVE_UP : OCTAVE_DOWN;

		for (auto i = 0; i < abs(octaveDifference); ++i)
		{
			emitKeyPress(octaveKey);
		}
	}

	uint8_t m_currentKey = 0;
	int8_t m_currentOctave = 0;
	HWND m_windowHandle = NULL;
};