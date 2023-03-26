#pragma once
#include <JuceHeader.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "../XenMIDIChannel.h"

class MIDIChannelModeButton : juce::TextButton
{
    

private:
    juce::uint16 channelNumber;
    XenMIDIChannel *thisChannel;
};
