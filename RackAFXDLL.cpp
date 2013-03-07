#include "RackAFXDLL.h"

// WARNING: DO NOT UNDER ANY CIRCUMSTANCES EDIT THIS FILE! **********************

/* VST Support
#include "audioeffect.h"
#include "Sock2VSTFactory.h"
END VST Support */

///////////////////////////////////////////////////////////
//
// Global variables
//
void* g_hModule;   // DLL module handle
static float g_fMUResult;

///////////////////////////////////////////////////////////
//
// DLL module information
//
extern "C"
{
	// entry point DllMain
	BOOL APIENTRY DllMain(HANDLE hModule,
						  DWORD dwReason,
						  void* lpReserved)
	{
		if (dwReason == DLL_PROCESS_ATTACH)
		{
			g_hModule = (HMODULE)hModule ;
		}
		return TRUE ;
	}
	// end entry point DllMain

/* VST Support
/* VST Support - DO NOT EDIT THIS CODE
	extern AudioEffect* createEffectInstance (audioMasterCallback audioMaster);

	#ifdef CODE_BLOX_MINGW
        #define VST_EXPORT DllExport
	#else
       #define VST_EXPORT
    #endif

	// VST Export Function
	VST_EXPORT AEffect* VSTPluginMain (audioMasterCallback audioMaster)
	{
		// Get VST Version of the Host
		if (!audioMaster (0, audioMasterVersion, 0, 0, 0, 0))
			return 0;  // old version

		// Create the AudioEffect
		AudioEffect* effect = createEffectInstance (audioMaster);
		if (!effect)
			return 0;

		// Return the VST AEffect structur
		return effect->getAeffect ();
	}
// end VSTPlugInMain 0x7FFD
END VST Support */

}

//RackAFX Creation Function
DllExport CPlugIn* createObject()
{
	CPlugIn* pOb = new CSpaceyDelayer(); // ***
	return pOb;
}

DllExport UINT getAPIVersion()
{
	return CURRENT_PLUGIN_API;
}

/* VST Support
// create VST object and attach the RackAFXPlugIn Buddy - DO NOT EDIT THIS CODE
AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	CPlugIn* pOb = new CSpaceyDelayer; // ***

	Sock2VSTFactory factory(pOb, audioMaster);
	return factory.getVSTPlugIn();
}
// end createEffectInstance 0x7FFE
END VST Support */


