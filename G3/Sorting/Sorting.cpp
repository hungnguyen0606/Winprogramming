// Sorting.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

typedef void(*Swapp)(int&, int &);
__declspec(dllexport) int aa = 8123;
struct  mypoint
{
	int x, y;
};

__declspec(dllexport) mypoint* createobject()
{
	return new mypoint();
}

__declspec(dllexport) void Sort(int *arr, int N)
{
	HINSTANCE hInst = LoadLibrary(L"Swapping");
	if (hInst != NULL)
	{
		Swapp pfn = (Swapp)GetProcAddress(hInst, "Swap");
		if (pfn != NULL)
		{
			for (int k = 0; k < N; ++k)
			{
				int j = k;
				for (int i = k + 1; i < N; ++i)
					if (arr[i] < arr[j])
						j = i;
				pfn(arr[k], arr[j]);
			}
		}
	}
}

__declspec(dllexport) void List(int *arr, int N)
{
	wchar_t s[500] = { TEXT('\0') };
	wchar_t buffer[500];
	for (int i = 0; i < N; ++i)
	{
		wsprintf(buffer, L"%d ", arr[i]);
		lstrcatW(s, buffer);
	}

	MessageBox(NULL, s, L"", MB_OK);
}