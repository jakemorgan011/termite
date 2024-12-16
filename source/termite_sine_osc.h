/*
  ==============================================================================

    termite_sine_osc.h
    Created: 22 Oct 2024 4:15:46pm
    Author:  Jake Morgan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "termite_data_types.h"

namespace termite {

// might need to check if we need to make a new struct everytime one of these is made.
struct sinOsc_params{
    float freq = 0.f;
    float gain = 0.f;
    float phase = 0.f;
};
class sinOsc{
    
public:
    
    sinOsc();
    ~sinOsc();
    
    void prepareToPlay(double inSampleRate);
    float return_current_sample();
    void setParams(float inFreq, bool isOnIn);
    
    
    // figure out if we use buffer here or something else.
    
private:
    
    bool isOn = false;
    tOscillator_Index oscIndex;
    sinOsc_params oscParams;
    float sampleRate = 44100.f;
    float phase = 0.f;
    double frequecy = 220;
    
};
}
