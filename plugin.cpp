#include "plugin.h"

CPlugIn::CPlugIn()
{
	// Normal Construction Stuff
	m_PlugInName = "Name Not Set.";
	m_uVersion = CURRENT_PLUGIN_API;

	m_bUseCustomVSTGUI = false;
	m_nGUIThemeID = 0xFFFFFFFF;
	m_nGUIType = -1;
	memset(&m_uControlTheme[0], 0, PLUGIN_CONTROL_THEME_SIZE*sizeof(UINT));
	m_uControlTheme[CONTROL_THEME] = 0xFFFFFFFF;

	// gen purpose arrays for future use extensions
	memset(&m_uPlugInEx[0], 0, PLUGIN_CONTROL_THEME_SIZE*sizeof(UINT));
	memset(&m_fPlugInEx[0], 0, PLUGIN_CONTROL_THEME_SIZE*sizeof(float));
	memset(&m_TextLabels[0], 0, PLUGIN_CONTROL_THEME_SIZE*sizeof(char*));
	memset(&m_uLabelCX[0], 0, PLUGIN_CONTROL_THEME_SIZE*sizeof(UINT));
	memset(&m_uLabelCY[0], 0, PLUGIN_CONTROL_THEME_SIZE*sizeof(UINT));

	m_bOutputOnlyPlugIn = false;
	m_uMaxInputChannels = 2;
	m_uMaxOutputChannels = 2;

	m_uX_TrackPadIndex = -1;
	m_uY_TrackPadIndex = -1;

	m_AssignButton1Name = "B1";
	m_AssignButton2Name = "B2";
	m_AssignButton3Name = "B3";

	m_bLatchingAssignButton1 = false;
	m_bLatchingAssignButton2 = false;
	m_bLatchingAssignButton3 = false;

	m_nNumWAVEChannels = 2;
	m_nSampleRate = 44100;
	m_nBitDepth = 16;

	// set this true if you want buffer data
	m_bWantBuffers = false;

	// set this true if you want VST buffer data
	m_bWantVSTBuffers = false;

	// set to true if you want IRs
	m_bWantIRs = false;

	// zero out the length
	m_nIRLength = 0;

	// use of MIDI controllers to adjust sliders/knobs
	m_bEnableMIDIControl = true;		// by default this is enabled
	m_bLinkGUIRowsAndButtons = false;	// crrently not used

	// for a user (not RackAFX) generated GUI - advanced you must compile your own resources
	m_bUserCustomGUI = false;

	// zero out impulse responses
	memset(&m_h_Left, 0, 1024*sizeof(float));
	memset(&m_h_Right, 0, 1024*sizeof(float));

	// create frequency table for MIDI support
	// make frequency (Hz) table
	double k = 1.059463094359;	// 12th root of 2
	double a = 6.875;	// a
	a *= k;	// b
	a *= k;	// bb
	a *= k;	// c, frequency of midi note 0
	for (int i = 0; i < 127; i++)	// 128 midi notes
	{
		// Hz Table
		m_MIDIFreqTable[i] = (float)a;

		// update for loop . . .
		a *= k;
	}

	m_pVectorJSProgram = new float[MAX_JS_PROGRAM_STEPS*MAX_JS_PROGRAM_STEP_VARS];
	memset(m_pVectorJSProgram, 0, MAX_JS_PROGRAM_STEPS*MAX_JS_PROGRAM_STEP_VARS*sizeof(float));

	m_JS_XCtrl.cControlName = "MIDI JS X";
	m_JS_XCtrl.uControlId = 0;
	m_JS_XCtrl.bMIDIControl = false;
	m_JS_XCtrl.uMIDIControlCommand = 176;
	m_JS_XCtrl.uMIDIControlName = 16;
	m_JS_XCtrl.uMIDIControlChannel = 0;

	m_JS_YCtrl.cControlName = "MIDI JS Y";
	m_JS_YCtrl.uControlId = 0;
	m_JS_YCtrl.bMIDIControl = false;
	m_JS_YCtrl.uMIDIControlCommand = 176;
	m_JS_YCtrl.uMIDIControlName = 17;
	m_JS_YCtrl.uMIDIControlChannel = 0;

	for(int i=0; i<PRESET_COUNT; i++)
	{
		m_PresetJSPrograms[i] = NULL;
		m_PresetNames[i] = NULL;
		m_AddlPresetValues[i] = NULL;
	}
}

CPlugIn::~CPlugIn(void)
{
	int nCount = m_UIControlList.count();
	for(int j=nCount-1; j>=0; j--)
	{
		CUICtrl* p = m_UIControlList.getAt(j);
		m_UIControlList.del(*p);
	}

	delete [] m_pVectorJSProgram;

	for(int i=0; i<PRESET_COUNT; i++)
	{
		if(m_PresetJSPrograms[i])
		{
			delete [] m_PresetJSPrograms[i];
			 m_PresetJSPrograms[i] = NULL;
		}

		if(m_AddlPresetValues[i])
		{
			delete [] m_AddlPresetValues[i];
			 m_AddlPresetValues[i] = NULL;
		}
	}
}

bool __stdcall CPlugIn::initialize()
{
	return true;
}

bool __stdcall CPlugIn::initUI()
{
	return true;
}


bool __stdcall CPlugIn::prepareForPlay()
{

	return true;
}


bool __stdcall CPlugIn::processAudioFrame(float* pInputBuffer, float* pOutputBuffer, UINT uNumInputChannels, UINT uNumOutputChannels)
{
	return true;
}


bool __stdcall CPlugIn::processSocketAudioBuffer(float* pInputBuffer, float* pOutputBuffer, UINT uNumInputChannels, UINT uNumOutputChannels, UINT uBufferSize)
{
	return true;
}


bool __stdcall CPlugIn::processVSTAudioBuffer(float** ppInputs, float** ppOutputs, UINT uNumChannels, int uNumFrames)
{
	return true;
}


bool __stdcall CPlugIn::userInterfaceChange(int nControlIndex)
{
	return true;
}

bool __stdcall CPlugIn::joystickControlChange(float fControlA, float fControlB, float fControlC, float fControlD, float fACMix, float fBDMix)
{
	return true;
}

bool __stdcall CPlugIn::midiNoteOn(UINT uChannel, UINT uMIDINote, UINT uVelocity)
{
	return true;
}

bool __stdcall CPlugIn::midiNoteOff(UINT uChannel, UINT uMIDINote, UINT uVelocity, bool bAllNotesOff)
{
	return true;
}

bool __stdcall CPlugIn::midiModWheel(UINT uChannel, UINT uModValue)
{
	return true;
}

bool __stdcall CPlugIn::midiPitchBend(UINT uChannel, int nActualPitchBendValue, float fNormalizedPitchBendValue)
{
	return true;
}

bool __stdcall CPlugIn::midiClock()
{
	return true;
}

bool __stdcall CPlugIn::midiMessage(unsigned char cChannel, unsigned char cStatus, unsigned char
						   cData1, unsigned char cData2)
{
	return true;
}

CUICtrl* CPlugIn::getUICtrlByControlID(UINT uID)
{
	int nCount = m_UIControlList.count();
	for(int i=0; i<nCount; i++)
	{
		CUICtrl* p = m_UIControlList.getAt(i);
		if(p->uControlId == uID)
			return p;
	}

	return NULL;
}

//-----------------------------------------------------------------------------------------
// sider moved between 0 and 1
//
// NOTE: this also sets the preset's variable too
void CPlugIn::setParameter (UINT index, float value)
{
	if(index < 0) return;

	CUICtrl* pUICtrl = m_UIControlList.getAt(index);
	if(!pUICtrl)
	{
		return;
	}

	// auto cook the data first
	switch(pUICtrl->uUserDataType)
	{
		case intData:
			*(pUICtrl->m_pUserCookedIntData) = calcDisplayVariable(pUICtrl->fUserDisplayDataLoLimit, pUICtrl->fUserDisplayDataHiLimit, value);
			break;

		case floatData:
			*(pUICtrl->m_pUserCookedFloatData) = calcDisplayVariable(pUICtrl->fUserDisplayDataLoLimit, pUICtrl->fUserDisplayDataHiLimit, value);
			break;

		case doubleData:
			*(pUICtrl->m_pUserCookedDoubleData) = calcDisplayVariable(pUICtrl->fUserDisplayDataLoLimit, pUICtrl->fUserDisplayDataHiLimit, value);
			break;

		case UINTData:
			*(pUICtrl->m_pUserCookedUINTData) = calcDisplayVariable(pUICtrl->fUserDisplayDataLoLimit, pUICtrl->fUserDisplayDataHiLimit, value);
			break;

		default:
			break;
	}

	// call the interface function
	userInterfaceChange(pUICtrl->uControlId);
}

//-----------------------------------------------------------------------------------------
// return the 0->1 version of the variable
float CPlugIn::getParameter (UINT index)
{
	if(index < 0) return 0.0;

	CUICtrl* pUICtrl = m_UIControlList.getAt(index);

	if(!pUICtrl)
	{
		return 0.0;
	}

	float fRawValue = 0;
	switch(pUICtrl->uUserDataType)
	{
		case intData:
		{
			fRawValue = calcSliderVariable(pUICtrl->fUserDisplayDataLoLimit, pUICtrl->fUserDisplayDataHiLimit, *(pUICtrl->m_pUserCookedIntData));
			break;
		}

		case floatData:
		{
			fRawValue = calcSliderVariable(pUICtrl->fUserDisplayDataLoLimit, pUICtrl->fUserDisplayDataHiLimit, *(pUICtrl->m_pUserCookedFloatData));
			break;
		}

		case doubleData:
		{
			fRawValue = calcSliderVariable(pUICtrl->fUserDisplayDataLoLimit, pUICtrl->fUserDisplayDataHiLimit, *(pUICtrl->m_pUserCookedDoubleData));
			break;
		}

		case UINTData:
		{
			fRawValue = calcSliderVariable(pUICtrl->fUserDisplayDataLoLimit, pUICtrl->fUserDisplayDataHiLimit, *(pUICtrl->m_pUserCookedUINTData));
			break;
		}

		default:
			break;
	}

	return fRawValue;
}

// --- special functions for saving common data types in the presets
//     use for variables that are NOT linked to a control (slider, button)
int CPlugIn::getNumAddtlPresets()
{
	return 0;
}

// value: a float from 0.0 to 1.0 that you saved
//        you must convert back to meaningful (cooked) data
void CPlugIn::setAddtlPresetValue(UINT index, float value)
{

}

// return -1 if variable not found
// Otherwise return a value from 0.0 to 1.0 that represents your data
float CPlugIn::getAddtlPresetValue(UINT index)
{
	return -1;
}

#if defined _WINDOWS || defined _WINDLL

// for user generated GUIs
//
// Return the Safe Window Handle of your Custom GUI
// or NULL if creation fails
HWND __stdcall CPlugIn::showGUI(HWND hParentWnd)
{
	return NULL;
}

// hide your GUI
void __stdcall CPlugIn::hideGUI()
{
}

// refresh your GUI controls
void __stdcall CPlugIn::refreshGUI()
{
}

void CPlugIn::sendUpdateGUI()
{
	if(m_hParentWnd)
		SendMessage(m_hParentWnd, SEND_UPDATE_GUI, 0, 0);
}

void CPlugIn::sendStatusWndText(char* pText)
{
	char   cText[1024];
    strncpy(cText, pText, 1023);
    cText[1023] = '\0';

	if(m_hParentWnd)
		SendMessage(m_hParentWnd, SEND_STATUS_WND_MESSAGE, 0, (LPARAM)&cText[0]);
}

void CPlugIn::sendSliderCtrlUpdate(UINT uID)
{
	if(m_hParentWnd)
		PostMessage(m_hParentWnd, UPDATE_SLIDER_CONTROL, 0, (LPARAM)uID);
}

void CPlugIn::sendAssignableButtonClick(UINT uID)
{
	if(m_hParentWnd)
		PostMessage(m_hParentWnd, SEND_ASGN_BUTTON_CLICK, 0, (LPARAM)uID);
}

/* caller must delete the returned char* when done
	call like this:

	char* pDLLpath = getMyDLLDirectory();
	.. do something with the string

	delete [] pDLLPath; // its an array so you use []

*/
char* CPlugIn::getMyDLLDirectory()
{
	HMODULE hmodule = GetModuleHandle(m_PlugInName);

	char dir[MAX_PATH];
	memset(&dir[0], 0, MAX_PATH*sizeof(char));
	dir[MAX_PATH-1] = '\0';

	if (hmodule)
		GetModuleFileName(hmodule, &dir[0], MAX_PATH);

	char* pDLLRoot = new char[MAX_PATH];

	int nLenDir = strlen(dir);
	int nLenDLL = strlen(m_PlugInName) + 5; // .dll = 4
	memcpy(pDLLRoot, &dir[0], nLenDir-nLenDLL);
	pDLLRoot[nLenDir-nLenDLL] = '\0';

	return pDLLRoot;
}

#endif

