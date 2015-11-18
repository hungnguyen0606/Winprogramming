// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
#include <windowsx.h>
#define MYRED 0
#define MYGREEN 1
#define MYBLUE 2
const COLORREF linecolor[] = {RGB(255,0,0), RGB(0,255,0), RGB(0,0,255)};
