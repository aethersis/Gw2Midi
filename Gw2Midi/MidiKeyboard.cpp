#include "stdafx.h"
#include "MidiKeyboard.h"

void MidiKeyboard::processMidiKey(DWORD midiEvent)
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

inline uint8_t MidiKeyboard::eventToNoteId(DWORD midiEvent, bool & success)
{
	bool noteOn = ((midiEvent & 0x000000ff) == 0x00000090);
	auto note = (midiEvent & 0x0000ff00) >> 8;

	success = noteOn;

	return (uint8_t)note;
}

int8_t MidiKeyboard::noteToOctave(uint8_t noteId)
{
	const uint8_t semitonesInOctave = 12;
	return noteId / semitonesInOctave;
}

char MidiKeyboard::noteToKey(uint8_t note)
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

void MidiKeyboard::emitKeyPress(char key)
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
}

void MidiKeyboard::emitNewOctave(uint8_t currentOctave, uint8_t newOctave)
{
	int octaveDifference = newOctave - currentOctave;
	char octaveKey = octaveDifference > 0 ? OCTAVE_UP : OCTAVE_DOWN;

	for (auto i = 0; i < abs(octaveDifference); ++i)
	{
		emitKeyPress(octaveKey);
	}
}
