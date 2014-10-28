#ifndef __SAFEAUDIOPROCESSOREDITOR__
#define __SAFEAUDIOPROCESSOREDITOR__

class SAFEAudioProcessorEditor : public AudioProcessorEditor,
                                 public Button::Listener,
                                 public Slider::Listener,
                                 public MultiTimer
{
public:
    //==========================================================================
    //      Constructor and Destructor
    //==========================================================================
    SAFEAudioProcessorEditor (SAFEAudioProcessor* ownerFilter);
    virtual ~SAFEAudioProcessorEditor();

    //==========================================================================
    //      User Interaction Listeners
    //==========================================================================
    void buttonClicked (Button* button);
    void sliderValueChanged (Slider* slider);
    void sliderDragStarted (Slider* slider);
    void sliderDragEnded (Slider* slider);
    virtual void sliderUpdate (Slider*) {}

    //==========================================================================
    //      GUI Update Timer
    //==========================================================================
    void timerCallback (int timerID);
    virtual void updateUI() {};
    virtual void updateMeters() {};

    //==========================================================================
    //      Externally Flag Warning
    //==========================================================================
    void flagWarning (WarningID id);

protected:
    TextEditor descriptorBox;
    SAFEButton recordButton, loadButton, metaDataButton, fileAccessButton, infoButton;
    OwnedArray <SAFESlider> sliders;

    //==========================================================================
    //      Set Position of Extra Screens
    //==========================================================================
    void setExtraScreenPosition (int x, int y);

private:
    enum Timers
    {
        parameterUpdateTimer,
        warningTimer,
        meterTimer
    };

    enum ExtraScreenLocation
    {
        Left,
        Right,
        Top,
        Bottom
    };

    bool warningVisible;
    String savedDescriptorBoxContent;

    bool fileAccessButtonPressed;

    //==========================================================================
    //      Extra Screen Bits
    //==========================================================================
    ComponentAnimator animator;

    SAFEMetaDataScreen metaDataScreen;
    File metaDataFile;
    ScopedPointer <XmlElement> metaDataElement;

    SAFEDescriptorLoadScreen descriptorLoadScreen;

    SAFEInfoScreen infoScreen;

    int extraScreenXPos, extraScreenYPos;
    bool extraScreenVisible;

    void showExtraScreen (SAFEExtraScreen& screenToShow);
    void hideExtraScreen (SAFEExtraScreen& screenToHide, ExtraScreenLocation direction);

    int numParameters;
    const OwnedArray <SAFEParameter>& parameters;

    ScopedPointer <SAFELookAndFeel> lookAndFeel;

    //==========================================================================
    //      Show Warning Messages in Text Box
    //==========================================================================
    bool warningFlagged;
    WarningID flaggedWarningID;
    void displayWarning (WarningID id, int durationInMilliseconds = 1000);

    //==========================================================================
    //      Test Connection to Server
    //==========================================================================
    bool canReachServer();

    //==========================================================================
    //      Parameter Logging
    //==========================================================================
    File parameterLogFile;
    void logAction (const String &logString);
    void logBlankLine();

    SAFEAudioProcessor* getProcessor()
    {
        return static_cast <SAFEAudioProcessor*> (getAudioProcessor());
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SAFEAudioProcessorEditor);
};

#endif // __SAFEAUDIOPROCESSOREDITOR__
