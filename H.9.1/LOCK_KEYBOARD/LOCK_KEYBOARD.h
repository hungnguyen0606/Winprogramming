// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LOCK_KEYBOARD_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LOCK_KEYBOARD_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LOCK_KEYBOARD_EXPORTS
#define LOCK_KEYBOARD_API __declspec(dllexport)
#else
#define LOCK_KEYBOARD_API __declspec(dllimport)
#endif

// This class is exported from the LOCK_KEYBOARD.dll
class LOCK_KEYBOARD_API CLOCK_KEYBOARD {
public:
	CLOCK_KEYBOARD(void);
	// TODO: add your methods here.
};

extern LOCK_KEYBOARD_API int nLOCK_KEYBOARD;

LOCK_KEYBOARD_API int fnLOCK_KEYBOARD(void);
