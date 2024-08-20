// WideSupport by Wyrdgirn
#include "WideCharSupport.h"
#include "CustomTranslator.h"
#include "CMessages.h"
#include <stdio.h>
#include <plugin.h>

using namespace plugin;

// String Structure
typedef struct
{
	char oBuff[2048]; // Original text buffer
	wchar_t rBuff[2048]; // Replaced text buffer
}char_buff;

// String Buffer
char_buff *tBuff = NULL;

// Strings count
size_t strcount = 0;

bool WideSupport::initialized = false;

// Initialize the WideChar System...
bool WideSupport::Initialize(char *filename) 
{
	char inputfile[2048] = { 0 },
		privkey[20] = { 0 },
		privapp[20] = { 0 };

	sprintf(inputfile,"%sdirectFont\\Translations\\%s",paths::GetPluginDirPathA(),filename);

	if (!CustomTranslator::FileExist(inputfile))
	{
		Error("\"%s\" not found...",inputfile);
		return false;
	}

	DWORD textcount = GetPrivateProfileInt("General","Count",NULL,inputfile);

	tBuff = (char_buff*)calloc(textcount,sizeof(char_buff));

	strcount = 0;

	for (DWORD i = 0; i < textcount; i++)
	{
		FillMemory(tBuff[strcount].oBuff,2048,0);
		FillMemory(tBuff[strcount].rBuff,4096,0);

		sprintf(privapp,"str%d",i);
		GetPrivateProfileString(privapp,"GameString",NULL,tBuff[strcount].oBuff,2048,inputfile);

		if (tBuff[strcount].oBuff)
		{
			char textbuff[4096] = { 0 };
			GetPrivateProfileString(privapp, "WideString", NULL, textbuff, 2048, inputfile);
			int WideSize = MultiByteToWideChar(CP_UTF8,0,textbuff,strlen(textbuff),NULL,0);
			MultiByteToWideChar(CP_UTF8,0,textbuff,strlen(textbuff),tBuff[strcount].rBuff,WideSize);
		} else break;

		if(!tBuff[strcount].rBuff && i > 0)
			break;
		else if(tBuff[strcount].rBuff)
			strcount++;
	}

	if(strcount)
		initialized = true;

	return initialized;
}

bool WideSupport::Translate(char *intext, wchar_t* outtext)
{
	size_t CharSize = 0, OrigSize = 0, WideSize = 0;

	if (initialized)
	{
		for (size_t i = 0; i < strcount; i++)
		{
			CharSize = strlen(tBuff[i].oBuff);
			OrigSize = strlen(intext);
			WideSize = wcslen(tBuff[i].rBuff);
			if ((CharSize == OrigSize) && !strncmp(intext,tBuff[i].oBuff,CharSize))
			{
				if(!tBuff[i].rBuff)
					break;
				memcpy(outtext,tBuff[i].rBuff,WideSize*2);
				outtext[WideSize] = L'\0';
				return !wcsncmp(outtext,tBuff[i].rBuff,WideSize);
			}
		}
	}
	return false;
}

void WideSupport::InsertPlayerControlKeysInString(wchar_t *text, size_t size)
{
	size_t textlen = wcslen(text);
	char mbtext[2048] = { 0 };
	wchar_t wctext[2048] = { 0 }, fwctext[2048] = { 0 };
	for (size_t i = 0; i < textlen; i++)
	{
		if (!wcsncmp(&text[i], L"~k~~", 4) || !wcsncmp(&text[i], L"~K~~", 4))
		{
			for (size_t x = 4; x < (textlen - i); x++)
			{
				if (text[i + x] == '~')
				{
					memcpy_s(wctext, 2048, &text[i], x+1);
					bool usedeftext = false;
					int charsize = WideCharToMultiByte(CP_UTF8,0,wctext,wcslen(wctext),NULL,0,NULL,NULL);
					WideCharToMultiByte(CP_UTF8,0,wctext,wcslen(wctext),mbtext,charsize,NULL,NULL);
					CMessages::InsertPlayerControlKeysInString(mbtext);
					FillMemory(wctext,2048,0);
					charsize = MultiByteToWideChar(CP_UTF8,0,mbtext,strlen(mbtext),NULL,0);
					MultiByteToWideChar(CP_UTF8,0,mbtext,strlen(mbtext),wctext,charsize);
					memcpy_s(fwctext, 2048,text,i+1);
					memcpy_s(&fwctext[i],(2048-i),wctext,charsize);
					memcpy_s(&fwctext[i+charsize],(2048-(i+charsize)),&text[(i+x)+1],(textlen-(i+x)));
					FillMemory(text,wcslen(text),0);
					memcpy_s(text,size,fwctext,wcslen(fwctext));
				}
			}
		}
	}
}
