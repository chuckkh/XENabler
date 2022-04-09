#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <JuceHeader.h>

class XenMIDIChannel : juce::AudioProcessor
{
public:
	XenMIDIChannel(int ch) : channel(ch)
	{
		channelModes.addIfNotAlreadyThere("Off");
		channelModes.addIfNotAlreadyThere("Mono");
		channelModes.addIfNotAlreadyThere("Poly");
		int defaultMode = 0;
		addParameter(mode = new juce::AudioParameterChoice(
			"mode", 
			"Mode", 
			channelModes, 
			defaultMode, 
			"Channel Mode"
			)
		);
		addParameter(usedForControlInput = new juce::AudioParameterBool(
			"useForControlInput",
			"Use for Control Input",
			false
			)
		);
		//		addParameter(gain = new juce::AudioParameterFloat("gain", "Gain", 0.0f, 1.0f, 0.5f));
		//		addParameter(invertPhase = new juce::AudioParameterBool("invertPhase", "Invert Phase", false)); // [3]


	};

private:
	//juce::AudioParameterInt *channel;
	juce::AudioParameterChoice* mode = 0;
	static juce::StringArray channelModes;

	 juce::AudioParameterBool *usedForControlInput = false;
	 uint8_t channel;
	 enum class ChannelMode {
		 Off, Mono, Poly
	 };
	 ChannelMode modeOld = ChannelMode::Off;

	 std::vector<std::unique_ptr<AudioPluginInstance>> soundingInstances;

};

