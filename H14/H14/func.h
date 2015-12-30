#ifndef _FUNC_
#define _FUNC_

#define ERROR 1
#define MAX_BUF 32768
#define ALL -1
#define TAIL 3
#include <cstdio>
#include <malloc.h>
#include <cstring>
#include <algorithm>
#include <utility>
#include <functional>
#include "resource.h"
using namespace std;
struct data
{
	string source, destination, filename, threadname;

	HWND idLabel, idViewer;
	int posx, posy;
	//HWND hDlg;
	int size, offset;
	data()
	{
		//		source = destination = NULL;
	}
	~data()
	{

	}
};

int copyPartFile(FILE *s, FILE *d, int bytesToCopy, HWND hDlg, data* mdat);

int calcFileSize(FILE* f);
int copyFile(char *scr, char *des);
int copyFile(char* scr, char* des, int bytesToCopy);
int moveFile(char* scr, char* des);
int splitFile(char *scr, int sizePerFile);
int joinFile(const char *file);

#endif