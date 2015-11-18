// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DLL_HOOK_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DLL_HOOK_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DLL_HOOK_EXPORTS
#define DLL_HOOK_API __declspec(dllexport)
#else
#define DLL_HOOK_API __declspec(dllimport)
#endif

// This class is exported from the DLL_HOOK.dll
class DLL_HOOK_API CDLL_HOOK {
public:
	CDLL_HOOK(void);
	// TODO: add your methods here.
};

extern DLL_HOOK_API int nDLL_HOOK;

DLL_HOOK_API int fnDLL_HOOK(void);
