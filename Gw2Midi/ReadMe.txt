========================================================================
                      Gw2Midi Project Overview
========================================================================

Gw2Midi is an application that allows Guild Wars 2 players to use a MIDI
controller device (i.e. digital piano) to play in-game instruments.
The application translates keys pressed on the MIDI device into in-game
key bindings. It also supports arbitrary key bindings (see Usage and in-
stallation) and switches octaves automatically.


========================================================================
                       Usage and installation
========================================================================

To use the program, first make sure that the device you want to play
(i.e. digital piano) is set as the default MIDI device. Generally this
is set up automatically by Windows, provided that it is the only device
you are using.
Once the device is plugged in and set as default, simply launch the pro-
gram and the game. It doesn't matter whether you launch the Gw2Midi or 
the game first. Now you can play something on your MIDI device and the
notes should be translated from your real instrument into the in-game 
instrument (i.e. harp). The octaves will be switched automatically.

If no config file (config.txt) is present in the program directory, it 
will be generated automatically and default in-game key bindings will be 
used. After closing the application, it is possible to change the key
bindings in the configuration file. Keep in mind that the order of rows
in the configuration file must be maintained and only the second column
is modifiable. An example how to modify the config is given in the auto-
generated config.txt file. 
Currently no function keys are supported. This means you cannot bind
such keys as ctrl, shift, enter, esc etc. You can however bind textual
keys such as ~ . ; A 1 etc.
