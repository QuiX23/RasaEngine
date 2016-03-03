#include "MidiDebugger.h"

float MidiDebugger::sMidiKnob1=1.0f;
bool MidiDebugger::sMidiButton1=false;

void MidiDebugger::mycallback(double deltatime, std::vector< unsigned char > *message, void *userData)
{
	//Tests for port values
	/*
	unsigned int nBytes = message->size();
	
	for (unsigned int i = 0; i<nBytes; i++)
		std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
	if (nBytes > 0)
		std::cout << "stamp = " << deltatime << std::endl;
	*/

	switch (message->at(1))
	{
		case BUTTON1:
			if (message->at(2)==127)
				sMidiButton1 = true;
			else
				sMidiButton1 = false;
			break;
		
		case KNOB1:
			sMidiKnob1 = ((float) message->at(2)) / 127.0f;
			break;
		default:
			break;
	}

	//Tests for button values
	/*
	std::cout << "Button1 " << sMidiButton1 << std::endl;
	//std::cout << "Knob1 " << sMidiKnob1 << std::endl;
	*/
}

MidiDebugger::MidiDebugger()
{

	midiin = std::make_unique<RtMidiIn>();
	// Check available ports.
	unsigned int nPorts = midiin->getPortCount();
	if (nPorts == 0) {
		std::cout << "No ports available!\n";
		throw _exception();
	}
	midiin->openPort(0);
	// Set our callback function.  This should be done immediately after
	// opening the port to avoid having incoming messages written to the
	// queue.
	midiin->setCallback(&mycallback);
	// Don't ignore sysex, timing, or active sensing messages.
	midiin->ignoreTypes(false, false, false);
	// Clean up
}


MidiDebugger::~MidiDebugger()
{
}
