#include "MainComponent.h"
//==============================================================================
MainComponent::MainComponent()
{
    textBoxTest.setFont(juce::Font(12));
    textBoxTest.setMultiLine(true);
    textBoxTest.setOpaque(false);
    //textBoxTest.setCaretVisible(true);
    // i don't know why. but if you just give this an adress it blows up.
    // having a pointer to a refernced listener works.
    textBoxTest.addListener(ptrToListener);
    //textBoxTestListener.textEditorReturnKeyPressed(textBoxTest) = [this]{};
    textBoxTest.onReturnKey = [this]{std::cout<<"enter_was_pressed";};
    
    oscData.current_sample_value = 0.f;
    
    textBoxTest.setReturnKeyStartsNewLine(true);
    textBoxTest.setColour(juce::TextEditor::ColourIds::backgroundColourId, juce::Colours::white);
    textBoxTest.setColour(juce::TextEditor::ColourIds::textColourId, juce::Colours::black);
    textBoxTest.setColour(juce::TextEditor::ColourIds::highlightColourId, juce::Colours::red);
    textBoxTest.setColour(juce::TextEditor::ColourIds::highlightedTextColourId, juce::Colours::white);
    
    addAndMakeVisible(textBoxTest);
    
    //compileButton->setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::black);
    //compileButton->setButtonText("compile");
    
    compileButton.reset(new juce::TextButton("compile"));
    compileButton->onClick = [this](){
        strTest.reset(new termite::termite_String("it works"));
        std::cout << *strTest << std::endl;
    
        juceConvert = textBoxTest.getText();
        charConvert = juceConvert.toRawUTF8();
        strTest.reset(new termite::termite_String(charConvert));
        
        check = text_interpret.isSin(strTest);
        
        //termite::juce2termite(juceConvert, strTest);
        
        std::cout << *strTest << " termite version" << std::endl;
        //bool on = text_interpret.isSin(strTest);
        
        
        
        
        DBG(textBoxTest.getText());
        //char* test = textBoxTest.getText();
        //if(std::is_same<textBoxTest.getText(), std::string>::value)
    };
//    if(_command_b_pressed(command, upKey)){
//        DBG(textBoxTest.getText());
//    }
    
    
    addAndMakeVisible(compileButton.get());
    
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (700, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    
    sinOsc.prepareToPlay(sampleRate);
    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    float* leftChannel = bufferToFill.buffer->getWritePointer(0);
    float* rightChannel = bufferToFill.buffer->getWritePointer(1);
    
    int num_samples = bufferToFill.buffer->getNumSamples();
    
    for(int i = 0; i < num_samples; i++){
        leftChannel[i] = sinOsc.return_current_sample();
        rightChannel[i] = sinOsc.return_current_sample();
    }
    
    // need a checker to make sure sample rate is specified inside the text editor, if not use defualt 44100
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    //bufferToFill.clearActiveBufferRegion();
    
    sinOsc.setParams(220, check);
}

void MainComponent::releaseResources()
{
    
    // ===========================================================
    // This is where we will "compile" the text we create inside the editor
    // ===========================================================
    
    
    // ==========================================================
    // we will also be able to reset internal sample rate inside this function
    // ==========================================================
    
    
    
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::whitesmoke);

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    textBoxTest.setBounds(0,0,500,600);
    
    compileButton->setBounds(500,0,200,200);
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::checkforBrackets(juce::String currentText){
    
}


// so this does not work. guessing i need to call "this" and reset something.
bool MainComponent::_command_b_pressed(const juce::ModifierKeys& command_key, const juce::KeyPress& press_two){
    if(command_key.isCommandDown() == true && press_two.getKeyCode() == juce::KeyPress::upKey){
        DBG("compile command B");
        return true;
    }else{
        return false;
    }
}
