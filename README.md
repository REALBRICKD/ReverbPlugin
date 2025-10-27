# Multi-Slider Reverb Plugin
This project is a plugin that applies reverb effects to audio of your choice. It is primarily designed for Digital Audio Workstations (DAWs) such as Ableton, FL Studio, Audacity, etc... \
This was largely done as an exercise to fully understanding both C++ and the audio tools we use. Development has proven eye-opening, and being able to program your own tools is a valuable asset to anybody who regularly works with audio. A wealth of knowledge is involved including knowledge in both computer science and audio engineering, with more advanced plugins even requiring knowledge in circuitry or fourier transformations. \
It processes the signal based on parameters such as:
*Dampening (how quickly higher frequencies decay) 
*Room size (affects the "flavor" of the reverb)
*Wet/dry (how much to mix the pre-processed and post-processed signals in the output)
*Width (how far apart the audio output of the channels will render, giving the illusion of a "wide" sound).
<br>
<br>

# Usage
Video of the plugin in action.
<br>



https://github.com/user-attachments/assets/f9215aef-7af8-4ae5-9da6-093483170af3



<br>
In it, I modulate the different parameters on an audio example. 
<br>
<br>

# Production and Methodology
Written in C++, based on the JUCE framework. \
This plugin splits any incoming audio into a left and a right channel, which is the standard configuration for any kind of stereo audio processing. \
There are two primary components in the project - a Plugin Editor (responsible for the UI and linking it to the project's functionality) and Plugin Processor (core signal processing and functionality of the project). \
Due to dependence on the JUCE framework, there is a .jucer file that saves dependencies and configurations. 
<br>
<br>

# How to Run the Application
This application is designed to be hosted in DAWs as a .vst3 plugin, a format based on [Steinberg's VST3 SDK](https://github.com/steinbergmedia/vst3sdk) - the current industry standard. \
In order to load the project properly, you must use the included .jucer file to be opened with Projucer (The latest version can be found [Here](https://juce.com/download/). This allows porting to IDEs, and seamless loading of all dependencies. \
Once the source code is open, you can build the project, and copy the .vst3 file into your plugins folder (the search path is configurable in every DAW). From there, it can be scanned by your DAW of choice and run as a standard effects plugin. 
<br>
<br>

# Optimization and Roadmap
Audio programming requires a high degree of optimization due to the amount of operations taking place every second. Although the plugin performs well, I am hoping to optimize further through the use of helper functions.\
This is just the beginning for this plugin - I plan to: add additional effects and UI elements to make the plugin more robust and capable. 
* Add additional effects such as:
  * A stereo shaper 
  * A filter
    * Potentially generating custom ones
* Add additional UI elements and quality of life such as a
  * A spectrum analyzer
  * Different tabs
  * More visually appealing UI

