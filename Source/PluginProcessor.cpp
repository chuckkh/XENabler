#include "PluginProcessor.h"
#include "PluginEditor.h"

/*
Xen::PluginNamer::PluginNamer()
{
    File myFile = File::getSpecialLocation(File::currentApplicationFile);
    pluginName = myFile.getFileNameWithoutExtension();

}

const char* Xen::PluginNamer::getName()
{
    return pluginName.toRawUTF8();
}
*/



WrapperTestAudioProcessor::WrapperTestAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
#endif

{
    File myFile = File::getSpecialLocation(File::currentApplicationFile);
    //    int myComp = 99;
    String tempName = myFile.getFileName();
    int tempLen = tempName.length();
    String Xname = tempName.substring(0,1);
    int myComp = Xname.compare("X");

    int charactersToStripFromBeginningOfName = 1; // "X"
    int charactersToStripFromEndOfName = 0; // 5 = ".vst3"

    String realFileName = myFile.getFileName().substring(
        charactersToStripFromBeginningOfName,
        tempLen - charactersToStripFromEndOfName
    );
//    realFileName = "Surge.vst3";

//    jassert(myComp == 0);

    fm.addDefaultFormats();
    descr.pluginFormatName = "VST3";
    File myPath = myFile.getParentDirectory();
    const String myPathName = myPath.getFullPathName();

    static String myPathNameSep = File::addTrailingSeparator(myPathName);
    realFullPathName = myPathNameSep + realFileName;
    descr.fileOrIdentifier = realFullPathName;

    for (uint32 i = 0; i < fm.getNumFormats(); ++i)
        plist.scanAndAddFile(realFullPathName,
            true,
            pluginDescriptions,
            *fm.getFormat(i));

    jassert(pluginDescriptions.size() > 0);

    bool loadingSuccess = false;
    String ignore;
    if (wrappedInstance = fm.createPluginInstance(*pluginDescriptions[0], 44100.0, 512, ignore))
        loadingSuccess = true;

    jassert(loadingSuccess);
}

WrapperTestAudioProcessor::~WrapperTestAudioProcessor()
{
}

const juce::String WrapperTestAudioProcessor::getName() const
{
    return JucePlugin_Name;
    //return pluginNamer.getName();
}

bool WrapperTestAudioProcessor::acceptsMidi() const
{
    return wrappedInstance->acceptsMidi();
}

bool WrapperTestAudioProcessor::producesMidi() const
{
    return wrappedInstance->producesMidi();
}

bool WrapperTestAudioProcessor::isMidiEffect() const
{
    return wrappedInstance->isMidiEffect();
}

double WrapperTestAudioProcessor::getTailLengthSeconds() const
{
    return wrappedInstance->getTailLengthSeconds();
}

int WrapperTestAudioProcessor::getNumPrograms()
{
    return 1;
}

int WrapperTestAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WrapperTestAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String WrapperTestAudioProcessor::getProgramName(int index)
{
    return {};
}

void WrapperTestAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

void WrapperTestAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    wrappedInstance->prepareToPlay(sampleRate, samplesPerBlock);
}

void WrapperTestAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WrapperTestAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void WrapperTestAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    wrappedInstance->processBlock(buffer, midiMessages);
}

bool WrapperTestAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* WrapperTestAudioProcessor::createEditor()
{
    return new WrapperTestAudioProcessorEditor(*this);
}

juce::AudioProcessorEditor* WrapperTestAudioProcessor::getWrappedInstanceEditor()
{
    return { wrappedInstance->createEditor() };
}

void WrapperTestAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    wrappedInstance->getStateInformation(destData);
}

void WrapperTestAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    wrappedInstance->setStateInformation(data, sizeInBytes);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WrapperTestAudioProcessor();
}

