# TinyDrummer
Teensy 4.1 Eurorack sample player

## Requirements
 - [Teensy Variable Playback library from newdigate.](https://github.com/newdigate/teensy-variable-playback)
 - At least one [psram chip](https://www.pjrc.com/store/psram.html) soldered onto the teensy 4.1. You can also use 2 for 16mb of sample storage.
 - [Stereo Plate Reverb](https://github.com/hexeguitar/t40fx/tree/main/Hx_PlateReverb)

## File Structure
It's very important to have your samples in a specific structure. The Root should have a folder called samples. Inside that, are your kits with whatever name you like. Inside them, there must be a total of 8 wav files (16bit, 44.1khz) named 1-8.wav. Like This:
![File structure](https://github.com/otem/Eurorack/blob/master/tinyDrummer/other/samples.png?raw=true)

## MIDI CCs
MIDI is configured to listed to channel 11. This can be changed in the code.
 - 1-8  : Pitch for each sample
 - 9-16 : Decay for each sample
 - 17   : Filter Frequency
 - 18   : Reverb Mix
 - 19   : Reverb Size
 - 20   : Kit Selection
 - 50   : Reset all CCs to 0
