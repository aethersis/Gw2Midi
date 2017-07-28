#pragma once
#include <Windows.h>
#include <iostream>
#include "MidiKeyboard.h"

MidiKeyboard keyboard;

void CALLBACK processMidiEvent(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	if (wMsg == MIM_DATA)
	{
		keyboard.processMidiKey(dwParam1);
	}
	return;
}

void initMidi()
{
	HMIDIIN hMidiDevice = NULL;
	DWORD nMidiPort = 0;
	UINT nMidiDeviceNum;
	MMRESULT rv;

	nMidiDeviceNum = midiInGetNumDevs();
	if (nMidiDeviceNum == 0)
	{
		throw std::exception("No midi devices found.");
	}

	rv = midiInOpen(&hMidiDevice, nMidiPort, (DWORD)(void*)processMidiEvent, 0, CALLBACK_FUNCTION);
	if (rv != MMSYSERR_NOERROR)
	{
		throw std::exception("Cannot read default midi input device");
	}

	midiInStart(hMidiDevice);
}