#pragma once
#include <memory>

#include "MIDI/RtMidi.h"

#pragma region portValues
	#define KNOB1 ((unsigned char)0)
	#define BUTTON1 ((unsigned char)8)
#pragma endregion

class MidiDebugger
{	
	std::unique_ptr<RtMidiIn> midiin;
	static void mycallback(double deltatime, std::vector< unsigned char > *message, void *userData);
public:
	static float sMidiKnob1;
	static bool sMidiButton1;
	
	 MidiDebugger();
	~MidiDebugger();
};

