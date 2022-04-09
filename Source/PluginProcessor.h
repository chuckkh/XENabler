#pragma once

#include <JuceHeader.h>
#include "XenMIDIChannel.h"

class WrapperTestAudioProcessor : public juce::AudioProcessor
{
public:
    WrapperTestAudioProcessor();
    ~WrapperTestAudioProcessor() override;
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    juce::AudioProcessorEditor* getWrappedInstanceEditor();

    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

private:
    AudioPluginFormatManager fm;
    PluginDescription descr;
    OwnedArray<PluginDescription> pluginDescriptions;
    KnownPluginList plist;
    juce::OwnedArray<XenMIDIChannel> MIDIChannels[17];

//    const String realFileName = "Surge.vst3";
    String realFullPathName;
//    AudioProcessor* plugin;
    std::unique_ptr<AudioPluginInstance> wrappedInstance;
//    juce::Component::SafePointer<AudioPluginInstance> wrappedInstance;
   

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WrapperTestAudioProcessor)
};