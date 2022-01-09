#include "WideCharSupport.h"
#include "CustomTranslator.h"
#include <stdio.h>
#include <plugin.h>

using namespace plugin;

// Mmmmm... Maybe dynamics allocations works but...
// I'm like static alloc better :3
char WideSupport::tBuff[8192][2048] = { 0 };
DWORD WideSupport::iBuff[8192] = { 0 };

// Strings count
size_t WideSupport::cBuff = 0;

bool WideSupport::initialized = false;

// Initialize the WideChar System...
bool WideSupport::Initialize(char *filename) 
{
	char inputfile[2048] = { 0 },
		privkey[10] = { 0 },
		privapp[20] = { 0 };

	sprintf(inputfile,"%sdirectFont\\Translations\\%s",paths::GetPluginDirPathA(),filename);

	if (!CustomTranslator::FileExist(inputfile))
	{
		Error("\"%s\" not found...",inputfile);
		return false;
	}

	DWORD textcount = GetPrivateProfileInt("General","Count",NULL,inputfile);

	cBuff = 0;

	for (DWORD i = 0; i < textcount; i++)
	{

		FillMemory(tBuff[i],2048,0);

		sprintf(privapp,"wchar%d",i);
		iBuff[i] = GetPrivateProfileInt(privapp,"TextID",NULL,inputfile);

		if(iBuff[i])
			GetPrivateProfileString(privapp,"WideString",NULL,tBuff[i],2048,inputfile);

		if(!tBuff)
			break;

		cBuff++;
	}

	if(cBuff)
		initialized = true;

	return initialized;
}

// Get a unique ID from input text...
DWORD WideSupport::GetTextID(char* text, size_t size)
{
	DWORD RetVal = 0;

	for (size_t i = 0; i < size; i++)
	{
		RetVal += (text[i] + i);
	}

	return RetVal;
}

bool WideSupport::Translate(DWORD TextID, wchar_t* outtext)
{
	static wchar_t pBuff[2048] = { 0 };
	int WideSize = 0;

	FillMemory(pBuff,4096,0);

	if (initialized)
	{
		for (DWORD i = 0; i < cBuff; i++)
		{
			if (iBuff[i] == TextID)
			{
				if(!tBuff[i])
					break;

				WideSize = MultiByteToWideChar(CP_UTF8,0,tBuff[i],strlen(tBuff[i]),NULL,0);
				MultiByteToWideChar(CP_UTF8,0,tBuff[i],strlen(tBuff[i]),pBuff,WideSize);

				memcpy(outtext,pBuff,(wcslen(pBuff) * 2));
				return true;
			}
		}
	}
	return false;
}
