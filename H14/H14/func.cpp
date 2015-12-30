#include "stdafx.h"

#include "func.h"

using namespace std;
void printTail(int i, const char *scr, char *des)
{
	sprintf(des, "%s.%02d", scr, i);
}

int calcFileSize(FILE* f)
{
	int offset = ftell(f);
	fseek(f, 0, SEEK_END);
	int Size = ftell(f);
	fseek(f, offset, SEEK_SET);
	return Size;
}

int copyPartFile(FILE *s, FILE *d, int bytesToCopy, HWND hDlg, data* mdat) //copy "bytesToCopy" bytes from position s
{
	/*InvalidateRect(hDlg, NULL, TRUE);
	UpdateWindow(hDlg);*/
	HDC hdc = GetDC(hDlg);
	RECT rect;
//	GetWindowRect(idViewer, &rect);
	TCHAR per[20];
	if (bytesToCopy == ALL)
		bytesToCopy = calcFileSize(s) - ftell(s);
	
	char* buf = (char*)calloc(MAX_BUF, 1);
	
	int k;
	int total = bytesToCopy;

	while (bytesToCopy && (k = fread(buf, 1, min(MAX_BUF, bytesToCopy), s)))
		{
			if (bytesToCopy < k)
				k = bytesToCopy;
			fwrite(buf, 1, k, d);
			bytesToCopy -= k;

			if (hDlg != NULL)
			{
				
				//show on viewer
				int percent = (int)ceil( 1.0*(total-bytesToCopy) / total*100);
				//TODO: show the percentage on viewer
				//sprintf(per, "%d", percent);
				_stprintf_p(per, 10, L"%d", percent);
				TextOut(hdc, mdat->posx, mdat->posy, per, lstrlen(per));
				//SetDlgItemText(hDlg, idViewer, per);
				
			}
		}
	ReleaseDC(hDlg, hdc);
	if (buf != NULL)
		free(buf);
	if (bytesToCopy) //cannot copy enough 
		return ERROR;

	return 0;
}


int joinFile(const char *file)
{
	//file001[strlen(file001) - 3] = 0;
	FILE *d = fopen(file, "wb");
	if (d == NULL)
		return ERROR;

	for(int i = 1; ; ++i)
	{
	//	int xxx = strlen(file) + TAIL + 1;
		char *scr = new char[strlen(file) + TAIL +1];
		printTail(i, file, scr);
		scr[strlen(scr)] = 0;
		FILE *s = fopen(scr, "rb");
		if (s == NULL) //no more files to join
			break;
		fseek(d, 0, SEEK_END);
		if (copyPartFile(s, d, ALL, NULL, NULL) == ERROR)
			return ERROR;
		fclose(s);
		remove(scr);
		
		delete[] scr;
	}
	int x = fclose(d);
	return 0;
}