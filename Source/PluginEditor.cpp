#include "PluginProcessor.h"
#include "PluginEditor.h"

WrapperTestAudioProcessorEditor::WrapperTestAudioProcessorEditor(WrapperTestAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)//, wrappedEditor(audioProcessor.getWrappedInstanceEditor())
{
    //wrappedEditor = audioProcessor.getWrappedInstanceEditor();
//    wrappedEditor(audioProcessor.getWrappedInstanceEditor());
//    wrappedEditor.reset(audioProcessor.getWrappedInstanceEditor());
    wrappedEditor = audioProcessor.getWrappedInstanceEditor();
    addAndMakeVisible(wrappedEditor, -1);
    bool visible = wrappedEditor->isVisible();
    setSize(wrappedEditor->getWidth(), wrappedEditor->getHeight() + 60);
}

WrapperTestAudioProcessorEditor::~WrapperTestAudioProcessorEditor()
{
    
//    delete wrappedEditor;
}

void WrapperTestAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void WrapperTestAudioProcessorEditor::paintOverChildren(juce::Graphics& g)
{
    //    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void WrapperTestAudioProcessorEditor::resized()
{
    wrappedEditor->setTopLeftPosition(0, 60);
}