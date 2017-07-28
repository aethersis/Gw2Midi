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
		std::cout << "Press any key to exit.";
		std::cin.get();
	}

	std::cout << "Everything seems ok. Pressing a key on your MIDI keyboard will generate key event for Guild Wars 2.\n\n";

	while (!kbhit() && key != 'q')
	{
		key = getch();
	}
}

