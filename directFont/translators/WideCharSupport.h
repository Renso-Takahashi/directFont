// WideSupport by Wyrdgirn
#pragma once

#include <Windows.h>

class WideSupport
{
public:
	static bool Initialize(char *filename);
	static bool Translate(char *intext, wchar_t *outtext);
	static void InsertPlayerControlKeysInString(wchar_t *text);
	static bool initialized;
};