#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../XenMIDIChannel.h"

class MIDIChannelModeButton : juce::TextButton
{
    MIDIChannelModeButton()
      : TextButton ("OFF")
    {
      setSize (10, 24);
    }

    ~MIDIChannelModeButton()
    {
    }


private:
    juce::uint16 channelNumber;
    XenMIDIChannel *thisChannel;
};
