SpaceyDelayer
=============
A fun, VST-compatible audio processing plugin that emulates classic multitap tape delay hardware like the Boss RE-20. 

The novel feature of SpaceyDelayer is that the offset time between taps in the delay is configurable - in a typical multitap tape delay, the user can specify the time between the initial playback and the first delay, but with SpaceyDelayer, the interval between the plugin's 3 delay taps is also configurable. 

Nonlinear waveshaping and bandpass filtering round out the "tape" sound, emulating saturation and the frequency response weaknesses of these older devices. 

All of the DSP "guts" are contained within SpaceyDelayer.cpp and DDLModule.cpp - in each file's respective ProcessAudioFrame() function. 
