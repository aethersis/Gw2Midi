#pragma once
#include <Windows.h>
#include <cstdint>
#include <exception>

#define OCTAVE_UP '0'
#define OCTAVE_DOWN '9'

class MidiKeyboard
{
public:
	void processMidiKey(DWORD midiEvent);

private:
	uint8_t eventToNoteId(DWORD midiEvent, bool& success);
	int8_t noteToOctave(uint8_t noteId);
	char noteToKey(uint8_t note);
	void emitKeyPress(char key);
	void emitNewOctave(uint8_t currentOctave, uint8_t newOctave);

	uint8_t m_currentKey = 0;
	int8_t m_currentOctave = 0;
	HWND m_windowHandle = NULL;
};