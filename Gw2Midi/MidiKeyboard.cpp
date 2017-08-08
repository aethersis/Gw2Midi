#include "stdafx.h"
#include "MidiKeyboard.h"

MidiKeyboard::MidiKeyboard()
{
}

MidiKeyboard::MidiKeyboard(KeyConfig config) : m_keyConfig(config)
{
}

void MidiKeyboard::loadConfig(const KeyConfig& config)
{
	m_keyConfig = config;
}

void MidiKeyboard::processMidiKey(DWORD midiEvent)
{
	bool noteOn = false;
	m_currentNoteId = eventToNoteId(midiEvent, noteOn);

	if (noteOn)
	{
		auto octave = noteToOctave(m_currentNoteId);
		emitNewOctave(octave);
		emitKeyPress(noteToDirectXKey(m_currentNoteId));
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

char MidiKeyboard::noteToDirectXKey(uint8_t note)
{
	note = chromaticToDiatonic(note);
	char key = toupper(m_keyConfig.bindings[note]);
	auto dxKey = m_keyTranslations.find(key);

	if (dxKey != m_keyTranslations.end())
	{
		emitKeyPress(dxKey->second);
	}
	else
	{
		std::string exceptionMessage = "The requested key binding \'";
		exceptionMessage += key;
		exceptionMessage += "\' is not supported. Try a different character in the config.";
		throw std::exception(exceptionMessage.c_str());// << " current the note");
	}
}

/* Converts black keys into white keys. I.e. C# becomes C, D# becomes D etc.*/
uint8_t MidiKeyboard::chromaticToDiatonic(uint8_t note)
{
	uint8_t noteFromZero = note % 12;

	switch (noteFromZero)
	{
	case 0:
		return 0;
	case 1:
		return 0;
	case 2:
		return 1;
	case 3:
		return 1;
	case 4:
		return 2;
	case 5:
		return 3;
	case 6:
		return 3;
	case 7:
		return 4;
	case 8:
		return 4;
	case 9:
		return 5;
	case 10:
		return 5;
	case 11:
		return 6;
	}
}

void MidiKeyboard::emitKeyPress(WORD key)
{
	INPUT input;
	memset(&input, 0, sizeof(INPUT));

	input.type = INPUT_KEYBOARD;
	input.ki.wScan = key;
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));

	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

void MidiKeyboard::emitNewOctave(uint8_t newOctave)
{
	int octaveDifference = newOctave - m_currentOctave;
	auto octaveKey = octaveDifference > 0 ? m_keyConfig.bindings[KeyNames::OctaveUp] : m_keyConfig.bindings[KeyNames::OctaveDown];
	auto octaveKeyId = m_keyTranslations.find(octaveKey);
	m_currentOctave = newOctave;

	if (octaveKeyId != m_keyTranslations.end())
	{
		for (auto i = 0; i < abs(octaveDifference); ++i)
		{
			emitKeyPress(octaveKeyId->second);
		}
	}
	else
	{
		throw std::exception("Requested key binding for octave key not supported. Try a different character in the config.");
	}
}
