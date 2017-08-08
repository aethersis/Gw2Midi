// Gw2Midi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include "MidiReceiver.h"

int main()
{
	char key = ' ';
	try
	{
		initMidi();
	}
	catch (const std::exception& exception)
	{
		std::cout << "An error occured: " << exception.what() << std::endl;
		std::cout << "Press enter to quit.";
		std::cin.get();

		return 1;
	}

	std::cout << "Everything seems ok. Pressing a key on your MIDI keyboard will generate key event for Guild Wars 2.\nPress q to quit or simply close the window.\n";

	while (!_kbhit() && key != 'q')
	{
		key = _getch();
	}

	return 0;
}

