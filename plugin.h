/*
	RackAFX(TM)
	Applications Programming Interface
	Base Class Object Definition
	Copyright(C) Tritone Systems Inc. 2002-2012

	In order to write a RackAFX plug-in, you need to create a C++ object that is
	derived from the CPlugIn base class. Your plug-in must implement the constructor,
	destructor and virtual Plug-In API Functions below.
*/

#pragma once

// RackAFX Includes
#include "pluginconstants.h"

// RackAFX abstract base class for RackAFX Plug-Ins
class CPlugIn
{
public:
	// Plug-In API Member Methods:
	// The followung 5 methods must be impelemented for a meaningful Plug-In
	//
	// 1. One Time Initialization
	CPlugIn();

	// 2. One Time Destruction
	virtual ~CPlugIn(void);

	// 3. The Prepare For Play Function is called just before audio streams
	virtual bool __stdcall prepareForPlay();

	// 4. processAudioFrame() processes an audio input to create an audio output
	virtual bool __stdcall processAudioFrame(float* pInputBuffer, float* pOutputBuffer, UINT uNumInputChannels, UINT uNumOutputChannels);

	// 5. userInterfaceChange() occurs when the user moves a control.
	virtual bool __stdcall userInterfaceChange(int nControlIndex);


	// OPTIONAL ADVANCED METHODS ------------------------------------------------------------------------------------------------
	// These are more advanced; see the website for more details
	//
	
	// 6. initialize() is called once just after creation; if you need to use Plug-In -> Host methods
	//				   such as sendUpdateGUI(), you must do them here and NOT in the constructor
	virtual bool __stdcall initialize();

	// 7. joystickControlChange() occurs when the user moves a control.
	virtual bool __stdcall joystickControlChange(float fControlA, float fControlB, float fControlC, float fControlD, float fACMix, float fBDMix);

	// 8. process buffers instead of Frames: 
	// NOTE: set m_bWantBuffers = true to use this function
	virtual bool __stdcall processSocketAudioBuffer(float* pInputBuffer, float* pOutputBuffer, UINT uNumInputChannels, UINT uNumOutputChannels, UINT uBufferSize);

	// 9. rocess buffers instead of Frames: 
	// NOTE: set m_bWantVSTBuffers = true to use this function
	virtual bool __stdcall processVSTAudioBuffer(float** ppInputs, float** ppOutputs, UINT uNumChannels, int uNumFrames);

	// 10. MIDI Note On Event
	virtual bool __stdcall midiNoteOn(UINT uChannel, UINT uMIDINote, UINT uVelocity);

	// 11. MIDI Note Off Event
	virtual bool __stdcall midiNoteOff(UINT uChannel, UINT uMIDINote, UINT uVelocity, bool bAllNotesOff);

	// 12. MIDI Modulation Wheel uModValue = 0 -> 127
	virtual bool __stdcall midiModWheel(UINT uChannel, UINT uModValue);

	// 13. MIDI Pitch Bend 
	//					nActualPitchBendValue = -8192 -> 8191, 0 is center, corresponding to the 14-bit MIDI value
	//					fNormalizedPitchBendValue = -1.0 -> +1.0, 0 is at center by using only -8191 -> +8191
	virtual bool __stdcall midiPitchBend(UINT uChannel, int nActualPitchBendValue, float fNormalizedPitchBendValue);

	// 14. MIDI Timing Clock (Sunk to BPM) function called once per clock
	virtual bool __stdcall midiClock();

	// 15. all MIDI messages - 
	// NOTE: set m_bWantAllMIDIMessages true to get everything else (other than note on/off, ModWheel, PitchBend, Timing Clock)
	virtual bool __stdcall midiMessage(unsigned char cChannel, unsigned char cStatus, unsigned char cData1, unsigned char cData2);
	
	// 16. initUI() is called only once from the constructor; you do not need to write or call it. Do NOT modify this function
	virtual bool __stdcall initUI();

	// --- special functions for saving common data types in the presets
	//     use for variables that are NOT linked to a control (slider, button)
	virtual void setAddtlPresetValue(UINT index, float value);
	virtual float getAddtlPresetValue(UINT index);
	virtual int getNumAddtlPresets();

	// --- Output to Parent stuff using Windows Messaging System (optional/advanced)
	// NOTE this is Plug-In --> Client communication not available in all Plug-In APIs
#if defined _WINDOWS || defined _WINDLL
	// 17. Update the GUI - my internal variables changed; make the GUI reflect this
	void sendUpdateGUI();

	// 18. Output text to the status window
	void sendStatusWndText(char* pText);

	// 19. change an underlying variable in code, tell the UI to update the control (slider/knob)
	//     similar to sendUpdateGUI() but only does a single control
	void sendSliderCtrlUpdate(UINT uID);
	
	// 20. click and assignable button
	void sendAssignableButtonClick(UINT uID);
	// End Output to Parent stuff ---

	// 21. get the directory where this DLL is located
	char* CPlugIn::getMyDLLDirectory();

	// FOR CUSTOM GUIs
	// ptr to parent wnd for StatusWindow or VST Host
	HWND m_hParentWnd;	
	
	// for user (NOT RackAFX) generated resources/GUIs Functions 21-24
	virtual HWND __stdcall showGUI(HWND hParentWnd);
	virtual void __stdcall hideGUI();
	virtual void __stdcall refreshGUI();
#endif

	// set this to TRUE if you have your own GUI to use; not for RackAFX GUIs 
	bool m_bUserCustomGUI; 

	// Plug-In API Member Variables:
	//
	// Variables you CAN change in your code ----------------------------
	//
	// FLAGS: you can set these to indicate your plug-in wants something or is something
	// flag for Oscillator (output only) Plug-Ins / MIDI synth Pllug-ins
	bool m_bOutputOnlyPlugIn;

	// flag to rx all MIDI (note on/off, mod wheel, clock, pitchbend WILL STILL BE CALLED)
	bool m_bWantAllMIDIMessages;

	// flag to set to request impulse responses from the UI
	bool m_bWantIRs;
	
	// the length of the IR from 0 to 1024
	int m_nIRLength;

	// flag to set to request buffer data instead of frame data
	bool m_bWantBuffers;

	// flag for VST capable plugins to use the VST buffer system
	bool m_bWantVSTBuffers;

	// flag to enable/disable MIDI controllers
	bool m_bEnableMIDIControl;

	// flag to force link the rows and button banks for custom GUIs
	bool m_bLinkGUIRowsAndButtons;
	
	// Variables you CAN NOT change in your code (RackAFX changes them for you)-----------
	//
	// information about the current playing-wave file
	int m_nNumWAVEChannels;
	int m_nSampleRate;
	int m_nBitDepth;

	// RackAFX stuff --- This can also be called by advanced users hooking up a commercial plugin
	// to a RackAFX Kernel
	CUIControlList m_UIControlList;
	CUICtrl* getUICtrlByControlID(UINT uID);
	void setParameter(UINT index, float value);
	float getParameter(UINT index);

	// for VST Preset Support
	float*  m_PresetJSPrograms[PRESET_COUNT];
	char*  m_PresetNames[PRESET_COUNT];
	float*  m_AddlPresetValues[PRESET_COUNT];

	// Plug-In Members:
	char* m_PlugInName; // name for Socket

	UINT m_uVersion;	// versioning, RackAFX only
	
	// custom GUI stuff
	bool m_bUseCustomVSTGUI;
	int m_nGUIThemeID;
	int m_nGUIType;
	UINT m_uControlTheme[PLUGIN_CONTROL_THEME_SIZE];
	UINT m_uPlugInEx[PLUGIN_CONTROL_THEME_SIZE];
	float m_fPlugInEx[PLUGIN_CONTROL_THEME_SIZE];
	char*  m_TextLabels[PLUGIN_CONTROL_THEME_SIZE];
	UINT m_uLabelCX[PLUGIN_CONTROL_THEME_SIZE];
	UINT m_uLabelCY[PLUGIN_CONTROL_THEME_SIZE];

	// I/O capabilities
	UINT m_uMaxInputChannels;
	UINT m_uMaxOutputChannels;

	// for track pad
	int m_uX_TrackPadIndex;
	int m_uY_TrackPadIndex;

	// assignable buttons
	char* m_AssignButton1Name;
	char* m_AssignButton2Name;
	char* m_AssignButton3Name;
	bool m_bLatchingAssignButton1;
	bool m_bLatchingAssignButton2;
	bool m_bLatchingAssignButton3;

	// prebuilt table of MIDI Note Numbers --> Pitch Frequencies
	float m_MIDIFreqTable[128];

	// vector joystick program table
	float* m_pVectorJSProgram;
	CUICtrl m_JS_XCtrl; // joystick X control
	CUICtrl m_JS_YCtrl; // joystick Y control

	// impulse response buffers
	float m_h_Left[1024];
	float m_h_Right[1024];

	// --------------------------------------------------------------------------------------------
};

