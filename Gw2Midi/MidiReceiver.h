#pragma once
#include <Windows.h>
#include <iostream>
#include "MidiKeyboard.h"
#include "ConfigParser.h"

MidiKeyboard keyboard;

// I am aware that this file is messed up because it mixes functionality, however the WinAPI callback ruins everything. 
// I haven't found a way to call non-static class method using WinAPI callbacks so far...

void CALLBACK processMidiEvent(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	if (wMsg == MIM_DATA)
	{
		try
		{
			keyboard.processMidiKey(dwParam1);
		}
		catch (const std::exception& ex)
		{
			std::cout << "Key processing error: " << ex.what() << std::endl;
		}
	}
	return;
}

void initMidi(const std::string& configPath = "config.txt")
{
	try
	{
		ConfigParser parser(configPath);
		auto config = parser.getParsedConfig();
		keyboard.loadConfig(config);
	}
	catch (const std::exception &ex)
	{
		std::cout << "Config problem: " << ex.what() << std::endl;
	}

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