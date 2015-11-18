// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DLL_SHOW_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DLL_SHOW_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DLL_SHOW_EXPORTS
#define DLL_SHOW_API __declspec(dllexport)
#else
#define DLL_SHOW_API __declspec(dllimport)
#endif

// This class is exported from the DLL_SHOW.dll
class DLL_SHOW_API CDLL_SHOW {
public:
	CDLL_SHOW(void);
	// TODO: add your methods here.
};

extern DLL_SHOW_API int nDLL_SHOW;

DLL_SHOW_API int fnDLL_SHOW(void);
