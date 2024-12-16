#pragma once

#include <JuceHeader.h>
#include "termite_header.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    
    void checkforBrackets(juce::String currentText);
    void _compileupdate();
    bool _command_b_pressed(const juce::ModifierKeys& command_key, const juce::KeyPress& press_two);

private:
    //==============================================================================
    // Your private member variables go here...
    juce::TextEditor textBoxTest;
    juce::TextEditor::Listener textBoxTestListener;
    juce::TextEditor::Listener* ptrToListener = &textBoxTestListener;
    std::unique_ptr<juce::TextButton> compileButton;
    
    
    
    juce::ModifierKeys command;
    juce::KeyPress upKey;
    
    std::unique_ptr<termite::termite_String> strTest;
    termite::tOscillator_Index oscData;
    termite::text_interpret text_interpret;
    const char* charConvert;
    juce::String juceConvert;
    
    float sample_rate = 44100.f;
    bool check = false;
    
    termite::sinOsc sinOsc;
    


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
