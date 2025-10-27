# Multi-Slider Reverb Plugin
Apply reverb effects to audio of your choice - designed for Digital Audio Workstations such as Ableton, FL Studio, Audacity, etc... \
[Video of the plugin in action](https://cdn.discordapp.com/attachments/1425323266763128985/1432169798774689832/screen-recording_2025-10-27_00-39-39-896Z.webm?ex=69001390&is=68fec210&hm=2e1482a777f667297fd676262ccdaf03790efe35e43ddf2e281f421fa19cd2f3&)
# Production and Methodology
Written in C++, based on JUCE framework. \
This plugin splits any incoming audio into 2 channels, which is a standard configuration for any kind of stereo audio processing. It processes the signal based on parameters such as dampening (how quickly higher frequencies decay), room size (affects the "flavor" of the reverb), wet/dry (how much to mix the pre-processed and post-processed signals in the output), and width (how far apart the audio output of the channels will render).
# How to Run the Application
This application is designed to be rendered in DAWs as a .vst3 plugin, based on [Steinberg's VST3 SDK](https://github.com/steinbergmedia/vst3sdk) - the current industry standard. You can put it in your plugins folder (configurable in each DAW) and run it as an effects plugin.
# Optimization and Next Steps
Audio programming requires a high degree of optimization due to the amount of operations taking place every second. Although it performs well, I am hoping to optimize further through the use of helper functions.\
This is just the beginning for this plugin - I could add additional effects and UI elements to make the plugin more robust and capable. 
# Lessons Learned
This was largely done as an exercise to learn C++, as well as an exercise in fully understanding the audio tools we use. It has proven eye-opening, and being able to program your own tools is a valuable asset to anybody who regularly works with audio. A wealth of knowledge is involved, with more advanced plugins requiring knowledge in circuitry or fourier transformations.
