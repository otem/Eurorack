# TinyDrummer
Teensy 4.1 Eurorack sample player

## Requirements
 - [Teensy Variable Playback library from newdigate.](https://github.com/newdigate/teensy-variable-playback)
 - At least one [psram chip](https://www.pjrc.com/store/psram.html) soldered onto the teensy 4.1. You can also use 2 for 16mb of sample storage.
 - [Stereo Plate Reverb](https://github.com/hexeguitar/t40fx/tree/main/Hx_PlateReverb)

## MIDI CCs
 - 1-8  : Pitch for each sample
 - 9-16 : Decay for each sample
 - 17   : Filter Frequency
 - 18   : Reverb Mix
 - 19   : Reverb Size
 - 20   : Kit Selection
 - 50   : Reset all CCs to 0
