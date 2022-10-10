# Samps 2
Teensy 4.1 Eurorack sample player with 8 note polyphony.

[![Samps 2 Video](https://img.youtube.com/vi/VPkpoh57Xw4/hqdefault.jpg)](https://www.youtube.com/watch?v=VPkpoh57Xw4)

## Requirements
 - [Teensy Variable Playback library from newdigate.](https://github.com/newdigate/teensy-variable-playback)
 - At least one [psram chip](https://www.pjrc.com/store/psram.html) soldered onto the teensy 4.1. You can also use 2 for 16mb of sample storage.
 - [Stereo Plate Reverb](https://github.com/hexeguitar/t40fx/tree/main/Hx_PlateReverb)
 - MicroSD card
 - Full BOM is in schematic folder

## File Structure
It's very important to have your samples in a specific structure. The root should have a folder called samples. Inside that are your instruments with whatever name you like. Inside them, there must be a total of 8 wav files (16bit, 44.1khz) named 1-8.wav. Like This:

![File structure](https://github.com/otem/Eurorack/blob/master/Samps%202/other/file%20structure.png?raw=true)

If you don't have 8 files per instrument, just duplicate some of them to get a total of 8.

## MIDI CCs
MIDI is configured to listed to channel 2. This can be changed in the code.

 - 1  : Playback direction, note larger than 63 = forward, under 63 = reverse
 - 2  : Master velocity, can be used to turn up/down sample volume if digital clipping occurs
 - 3  : Reverb Mix
 - 4  : Reverb Size

