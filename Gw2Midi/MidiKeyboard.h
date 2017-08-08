#pragma once
#include <Windows.h>
#include <cstdint>
#include <exception>
#include <map>
#include "KeyConfig.h"

class MidiKeyboard
{
public:
	MidiKeyboard();
	MidiKeyboard(KeyConfig config);
	void loadConfig(const KeyConfig & config);
	void processMidiKey(DWORD midiEvent);

private:
	uint8_t eventToNoteId(DWORD midiEvent, bool& success);
	int8_t noteToOctave(uint8_t noteId);
	char noteToDirectXKey(uint8_t note);
	void emitKeyPress(WORD key);
	void emitNewOctave(uint8_t newOctave);
	uint8_t chromaticToDiatonic(uint8_t note);

	uint8_t m_currentNoteId = 0;
	int8_t m_currentOctave = 0;
	HWND m_windowHandle = NULL;
	KeyConfig m_keyConfig;
	const std::map<char, WORD> m_keyTranslations = { { '1',  0x0402 },
	                                                 { '2',  0x0403 },
	                                                 { '3',  0x0404 },
	                                                 { '4',  0x0405 },
	                                                 { '5',  0x0406 },
	                                                 { '6',  0x0407 },
	                                                 { '7',  0x0408 },
	                                                 { '8',  0x0409 },
	                                                 { '9',  0x040A },
	                                                 { '0',  0x040B },
	                                                 { 'Q',  0x0410 },
	                                                 { 'W',  0x0411 },
	                                                 { 'E',  0x0412 },
	                                                 { 'R',  0x0413 },
	                                                 { 'T',  0x0414 },
	                                                 { 'Y',  0x0415 },
	                                                 { 'U',  0x0416 },
	                                                 { 'I',  0x0417 },
	                                                 { 'O',  0x0418 },
	                                                 { 'P',  0x0419 },
	                                                 { 'A',  0x041E },
	                                                 { 'S',  0x041F },
	                                                 { 'D',  0x0420 },
	                                                 { 'F',  0x0421 },
	                                                 { 'G',  0x0422 },
	                                                 { 'H',  0x0423 },
	                                                 { 'J',  0x0424 },
	                                                 { 'K',  0x0425 },
	                                                 { 'L',  0x0426 },
	                                                 { 'Z',  0x042C },
	                                                 { 'X',  0x042D },
	                                                 { 'C',  0x042E },
	                                                 { 'V',  0x042F },
	                                                 { 'B',  0x0430 },
	                                                 { 'N',  0x0431 },
	                                                 { 'M',  0x0432 },
	                                                 { '[',  0x041A },
	                                                 { ']',  0x041B },
	                                                 { ';',  0x0427 },
	                                                 { '\'', 0x0428 },
	                                                 { '\\', 0x042B },
	                                                 { '/',  0x0435 },
	                                                 { ',',  0x0433 },
	                                                 { '.',  0x0434 },
	                                                 { '*',  0x0437 },
	                                                 { ' ',  0x0439 },
	                                                 { '+',  0x044E },
	                                                 { '-',  0x040C },
	                                                 { '=',  0x040D } };
};