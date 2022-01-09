#pragma once

#include <Windows.h>

class WideSupport
{
public:
	static bool Initialize(char *filename);
	static DWORD GetTextID(char* const text, size_t size);
	static bool Translate(DWORD TextID, wchar_t *outtext);
	static bool initialized;
protected:
	static char tBuff[8192][2048];
	static DWORD iBuff[8192];
	static size_t cBuff;
};