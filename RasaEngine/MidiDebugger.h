#pragma once
#include <memory>
#include "RtMidi.h"


class MidiDebugger
{
	std::unique_ptr<RtMidiIn> midiin;
	static void mycallback(double deltatime, std::vector< unsigned char > *message, void *userData);
public:
	//RtMidiIn* midiin;
	MidiDebugger();
	~MidiDebugger();
};

