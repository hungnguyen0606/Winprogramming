// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DLL_LIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DLL_LIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DLL_LIB_EXPORTS
#define DLL_LIB_API __declspec(dllexport)
#else
#define DLL_LIB_API __declspec(dllimport)
#endif

// This class is exported from the DLL_Lib.dll
class DLL_LIB_API CDLL_Lib {
public:
	CDLL_Lib(void);
	// TODO: add your methods here.
};

extern DLL_LIB_API int nDLL_Lib;

DLL_LIB_API int fnDLL_Lib(void);
DLL_LIB_API int Cong(int a, int b);
DLL_LIB_API int Tru(int a, int b);
DLL_LIB_API int Nhan(int a, int b);
DLL_LIB_API int Chia(int a, int b);
