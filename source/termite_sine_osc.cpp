/*
  ==============================================================================

    termite_sine_osc.cpp
    Created: 22 Oct 2024 4:15:46pm
    Author:  Jake Morgan

  ==============================================================================
*/

#include "termite_sine_osc.h"

using namespace termite;

sinOsc::sinOsc(){}

sinOsc::~sinOsc(){}

void sinOsc::prepareToPlay(double inSampleRate){
    sampleRate = inSampleRate;
}
// if finds frequency variable overload the sinOSc function
float sinOsc::return_current_sample(){
    float sine_out = std::sin(phase * 2 * juce::MathConstants<float>::pi);
    
    phase += frequecy / sampleRate;
    
    if(phase > 1.f){
        phase -= 1.f;
    }
    float onCheck = 0;
    if(isOn == false){
        onCheck = 0;
    }else{
            onCheck = 1;
    }
    return sine_out * onCheck;
}

void sinOsc::setParams(float inFreq, bool isOnIn){
    frequecy = inFreq;
    isOn = isOnIn;
}
