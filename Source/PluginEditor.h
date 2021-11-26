#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class WrapperTestAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    WrapperTestAudioProcessorEditor(WrapperTestAudioProcessor&);
    ~WrapperTestAudioProcessorEditor() override;
    void paint(juce::Graphics&) override;
    void paintOverChildren(juce::Graphics&) override;
    void resized() override;
private:
    WrapperTestAudioProcessor& audioProcessor;
    //std::unique_ptr<AudioProcessorEditor> wrappedEditor;
    juce::Component::SafePointer<AudioProcessorEditor> wrappedEditor;
//    std::unique_ptr<AudioProcessorEditor> wrappedEditor(audioProcessor->getWrappedInstanceEditor());

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WrapperTestAudioProcessorEditor)
};