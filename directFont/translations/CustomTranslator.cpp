/* ###############################################################

In this file are the functions that I have created to load custom
translators without having to recompile the mod, it can be used both
for common use and to correct characters easily.

You can edit the files and reload them in-game using the
cheat "fontconfig"...

################################################################*/

#include "CustomTranslator.h"
#include "CustomCharMap.h"
#include <stdio.h>
#include <plugin.h>

using namespace plugin;

static bool initialized[] = { false, false, false, false };

// Initialize the custom translator
bool CustomTranslator::Initialize(const char* filename)
{
	initialized[0] = false;
	initialized[1] = false;
	initialized[2] = false;
	initialized[3] = false;

	static char filenm[65];
	FillMemory(filenm, 65, 0);

	if(initialized[0])initialized[0] = false;
	if(initialized[1])initialized[1] = false;
	if(initialized[2])initialized[2] = false;
	if(initialized[3])initialized[3] = false;

	sprintf(filenm, "directFont\\Custom Maps\\%s0.wcm", filename);
	initialized[0] = LoadMap(filenm, 0);

	sprintf(filenm, "directFont\\Custom Maps\\%s1.wcm", filename);
	initialized[1] = LoadMap(filenm, 1);

	sprintf(filenm, "directFont\\Custom Maps\\%s2.wcm", filename);
	initialized[2] = LoadMap(filenm, 2);

	sprintf(filenm, "directFont\\Custom Maps\\%s3.wcm", filename);
	initialized[3] = LoadMap(filenm, 3);

	return ((initialized[0] || initialized[1] ||
			 initialized[2] || initialized[3]) ? true : false);
}

// Load the translation files
bool CustomTranslator::LoadMap(char* filename, char font)
{
	DWORD Header = 0, fSize = 0, CheckSum = 0, ChkSum = 0;
	WORD offset = 0, size = 0;
	unsigned char rbyte = 0, obyte = 0;
	bool result = false;
	FILE* CustomMap = NULL;

	CustomMap = fopen(PLUGIN_PATH(filename), "rb");

	if (CustomMap)
	{
		fseek(CustomMap, 0, SEEK_END);
		fSize = ftell(CustomMap);
		fseek(CustomMap, 0, SEEK_SET);

		fread(&Header, 4, 1, CustomMap);
		if (Header == 0x14D4357u || Header == 0x24D4357u ||
			Header == 0x34D4357u || Header == 0x44D4357u)
		{
			fseek(CustomMap, (fSize - 4), SEEK_SET);
			fread(&CheckSum, 4, 1, CustomMap);

			fseek(CustomMap, 0, SEEK_SET);
			for (size_t x = 0; x < (fSize - 5); x++)
			{
				fseek(CustomMap, x, SEEK_SET);
				fread(&rbyte, 1, 1, CustomMap);
				ChkSum += rbyte;
			}

			if (ChkSum == CheckSum) {

				fseek(CustomMap, 0x09, SEEK_SET);
				fread(&offset, 2, 1, CustomMap);
				fseek(CustomMap, 0x0B, SEEK_SET);
				fread(&size, 2, 1, CustomMap);

				fseek(CustomMap, offset, SEEK_SET);

				// FillMemory is not necessary in this case because
				// Memcpy is used to fill the buffer with the
				// original character map... 
				
				//FillMemory(fontmap[font], 208, 0);
				memcpy(fontmap[font], FillMap, 208);

				for (WORD x = 0; x < (size - 1); x++)
				{
					fseek(CustomMap, (offset + x), SEEK_SET);
					fread(&obyte, 1, 1, CustomMap);
					x++;
					fseek(CustomMap, (offset + x), SEEK_SET);
					fread(&rbyte, 1, 1, CustomMap);

					if(rbyte > 0)
						fontmap[font][obyte - 0x20] = rbyte;
				}
				result = true;

			}
			else {
				Error("CustomTranslator::LoadMap\nCustom Font %d checksum missmatch.\nData = %d\nfile = %d", (font + 1) ,ChkSum ,CheckSum);
				return false;
			}
		}
		fclose(CustomMap);
	}

	return result;
}

// Translate the characters using the custom translator
//
// Yes, I know that it is a bit long but it is the method
// that works best, the traditional one does not replace
// the characters 
void CustomTranslator::TranslateString(char* str, int font)
{
	if (initialized[font])
	{
		char *pText = str;
		while (*pText) {
			switch (*pText)
			{
				case '\x20':
					*pText = fontmap[font][0];
					break;
				case '\x21':
					*pText = fontmap[font][1];
					break;
				case '\x22':
					*pText = fontmap[font][2];
					break;
				case '\x23':
					*pText = fontmap[font][3];
					break;
				case '\x24':
					*pText = fontmap[font][4];
					break;
				case '\x25':
					*pText = fontmap[font][5];
					break;
				case '\x26':
					*pText = fontmap[font][6];
					break;
				case '\x27':
					*pText = fontmap[font][7];
					break;
				case '\x28':
					*pText = fontmap[font][8];
					break;
				case '\x29':
					*pText = fontmap[font][9];
					break;
				case '\x2A':
					*pText = fontmap[font][10];
					break;
				case '\x2B':
					*pText = fontmap[font][11];
					break;
				case '\x2C':
					*pText = fontmap[font][12];
					break;
				case '\x2D':
					*pText = fontmap[font][13];
					break;
				case '\x2E':
					*pText = fontmap[font][14];
					break;
				case '\x2F':
					*pText = fontmap[font][15];
					break;
				case '\x30':
					*pText = fontmap[font][16];
					break;
				case '\x31':
					*pText = fontmap[font][17];
					break;
				case '\x32':
					*pText = fontmap[font][18];
					break;
				case '\x33':
					*pText = fontmap[font][19];
					break;
				case '\x34':
					*pText = fontmap[font][20];
					break;
				case '\x35':
					*pText = fontmap[font][21];
					break;
				case '\x36':
					*pText = fontmap[font][22];
					break;
				case '\x37':
					*pText = fontmap[font][23];
					break;
				case '\x38':
					*pText = fontmap[font][24];
					break;
				case '\x39':
					*pText = fontmap[font][25];
					break;
				case '\x3A':
					*pText = fontmap[font][26];
					break;
				case '\x3B':
					*pText = fontmap[font][27];
					break;
				case '\x3C':
					*pText = fontmap[font][28];
					break;
				case '\x3D':
					*pText = fontmap[font][29];
					break;
				case '\x3E':
					*pText = fontmap[font][30];
					break;
				case '\x3F':
					*pText = fontmap[font][31];
					break;
				case '\x40':
					*pText = fontmap[font][32];
					break;
				case '\x41':
					*pText = fontmap[font][33];
					break;
				case '\x42':
					*pText = fontmap[font][34];
					break;
				case '\x43':
					*pText = fontmap[font][35];
					break;
				case '\x44':
					*pText = fontmap[font][36];
					break;
				case '\x45':
					*pText = fontmap[font][37];
					break;
				case '\x46':
					*pText = fontmap[font][38];
					break;
				case '\x47':
					*pText = fontmap[font][39];
					break;
				case '\x48':
					*pText = fontmap[font][40];
					break;
				case '\x49':
					*pText = fontmap[font][41];
					break;
				case '\x4A':
					*pText = fontmap[font][42];
					break;
				case '\x4B':
					*pText = fontmap[font][43];
					break;
				case '\x4C':
					*pText = fontmap[font][44];
					break;
				case '\x4D':
					*pText = fontmap[font][45];
					break;
				case '\x4E':
					*pText = fontmap[font][46];
					break;
				case '\x4F':
					*pText = fontmap[font][47];
					break;
				case '\x50':
					*pText = fontmap[font][48];
					break;
				case '\x51':
					*pText = fontmap[font][49];
					break;
				case '\x52':
					*pText = fontmap[font][50];
					break;
				case '\x53':
					*pText = fontmap[font][51];
					break;
				case '\x54':
					*pText = fontmap[font][52];
					break;
				case '\x55':
					*pText = fontmap[font][53];
					break;
				case '\x56':
					*pText = fontmap[font][54];
					break;
				case '\x57':
					*pText = fontmap[font][55];
					break;
				case '\x58':
					*pText = fontmap[font][56];
					break;
				case '\x59':
					*pText = fontmap[font][57];
					break;
				case '\x5A':
					*pText = fontmap[font][58];
					break;
				case '\x5B':
					*pText = fontmap[font][59];
					break;
				case '\x5C':
					*pText = fontmap[font][60];
					break;
				case '\x5D':
					*pText = fontmap[font][61];
					break;
				case '\x5E':
					*pText = fontmap[font][62];
					break;
				case '\x5F':
					*pText = fontmap[font][63];
					break;
				case '\x60':
					*pText = fontmap[font][64];
					break;
				case '\x61':
					*pText = fontmap[font][65];
					break;
				case '\x62':
					*pText = fontmap[font][66];
					break;
				case '\x63':
					*pText = fontmap[font][67];
					break;
				case '\x64':
					*pText = fontmap[font][68];
					break;
				case '\x65':
					*pText = fontmap[font][69];
					break;
				case '\x66':
					*pText = fontmap[font][70];
					break;
				case '\x67':
					*pText = fontmap[font][71];
					break;
				case '\x68':
					*pText = fontmap[font][72];
					break;
				case '\x69':
					*pText = fontmap[font][73];
					break;
				case '\x6A':
					*pText = fontmap[font][74];
					break;
				case '\x6B':
					*pText = fontmap[font][75];
					break;
				case '\x6C':
					*pText = fontmap[font][76];
					break;
				case '\x6D':
					*pText = fontmap[font][77];
					break;
				case '\x6E':
					*pText = fontmap[font][78];
					break;
				case '\x6F':
					*pText = fontmap[font][79];
					break;
				case '\x70':
					*pText = fontmap[font][80];
					break;
				case '\x71':
					*pText = fontmap[font][81];
					break;
				case '\x72':
					*pText = fontmap[font][82];
					break;
				case '\x73':
					*pText = fontmap[font][83];
					break;
				case '\x74':
					*pText = fontmap[font][84];
					break;
				case '\x75':
					*pText = fontmap[font][85];
					break;
				case '\x76':
					*pText = fontmap[font][86];
					break;
				case '\x77':
					*pText = fontmap[font][87];
					break;
				case '\x78':
					*pText = fontmap[font][88];
					break;
				case '\x79':
					*pText = fontmap[font][89];
					break;
				case '\x7A':
					*pText = fontmap[font][90];
					break;
				case '\x7B':
					*pText = fontmap[font][91];
					break;
				case '\x7C':
					*pText = fontmap[font][92];
					break;
				case '\x7D':
					*pText = fontmap[font][93];
					break;
				case '\x7E':
					*pText = fontmap[font][94];
					break;
				case '\x7F':
					*pText = fontmap[font][95];
					break;
				case '\x80':
					*pText = fontmap[font][96];
					break;
				case '\x81':
					*pText = fontmap[font][97];
					break;
				case '\x82':
					*pText = fontmap[font][98];
					break;
				case '\x83':
					*pText = fontmap[font][99];
					break;
				case '\x84':
					*pText = fontmap[font][100];
					break;
				case '\x85':
					*pText = fontmap[font][101];
					break;
				case '\x86':
					*pText = fontmap[font][102];
					break;
				case '\x87':
					*pText = fontmap[font][103];
					break;
				case '\x88':
					*pText = fontmap[font][104];
					break;
				case '\x89':
					*pText = fontmap[font][105];
					break;
				case '\x8A':
					*pText = fontmap[font][106];
					break;
				case '\x8B':
					*pText = fontmap[font][107];
					break;
				case '\x8C':
					*pText = fontmap[font][108];
					break;
				case '\x8D':
					*pText = fontmap[font][109];
					break;
				case '\x8E':
					*pText = fontmap[font][110];
					break;
				case '\x8F':
					*pText = fontmap[font][111];
					break;
				case '\x90':
					*pText = fontmap[font][112];
					break;
				case '\x91':
					*pText = fontmap[font][113];
					break;
				case '\x92':
					*pText = fontmap[font][114];
					break;
				case '\x93':
					*pText = fontmap[font][115];
					break;
				case '\x94':
					*pText = fontmap[font][116];
					break;
				case '\x95':
					*pText = fontmap[font][117];
					break;
				case '\x96':
					*pText = fontmap[font][118];
					break;
				case '\x97':
					*pText = fontmap[font][119];
					break;
				case '\x98':
					*pText = fontmap[font][120];
					break;
				case '\x99':
					*pText = fontmap[font][121];
					break;
				case '\x9A':
					*pText = fontmap[font][122];
					break;
				case '\x9B':
					*pText = fontmap[font][123];
					break;
				case '\x9C':
					*pText = fontmap[font][124];
					break;
				case '\x9D':
					*pText = fontmap[font][125];
					break;
				case '\x9E':
					*pText = fontmap[font][126];
					break;
				case '\x9F':
					*pText = fontmap[font][127];
					break;
				case '\xA0':
					*pText = fontmap[font][128];
					break;
				case '\xA1':
					*pText = fontmap[font][129];
					break;
				case '\xA2':
					*pText = fontmap[font][130];
					break;
				case '\xA3':
					*pText = fontmap[font][131];
					break;
				case '\xA4':
					*pText = fontmap[font][132];
					break;
				case '\xA5':
					*pText = fontmap[font][133];
					break;
				case '\xA6':
					*pText = fontmap[font][134];
					break;
				case '\xA7':
					*pText = fontmap[font][135];
					break;
				case '\xA8':
					*pText = fontmap[font][136];
					break;
				case '\xA9':
					*pText = fontmap[font][137];
					break;
				case '\xAA':
					*pText = fontmap[font][138];
					break;
				case '\xAB':
					*pText = fontmap[font][139];
					break;
				case '\xAC':
					*pText = fontmap[font][140];
					break;
				case '\xAD':
					*pText = fontmap[font][141];
					break;
				case '\xAE':
					*pText = fontmap[font][142];
					break;
				case '\xAF':
					*pText = fontmap[font][143];
					break;
				case '\xB0':
					*pText = fontmap[font][144];
					break;
				case '\xB1':
					*pText = fontmap[font][145];
					break;
				case '\xB2':
					*pText = fontmap[font][146];
					break;
				case '\xB3':
					*pText = fontmap[font][147];
					break;
				case '\xB4':
					*pText = fontmap[font][148];
					break;
				case '\xB5':
					*pText = fontmap[font][149];
					break;
				case '\xB6':
					*pText = fontmap[font][150];
					break;
				case '\xB7':
					*pText = fontmap[font][151];
					break;
				case '\xB8':
					*pText = fontmap[font][152];
					break;
				case '\xB9':
					*pText = fontmap[font][153];
					break;
				case '\xBA':
					*pText = fontmap[font][154];
					break;
				case '\xBB':
					*pText = fontmap[font][155];
					break;
				case '\xBC':
					*pText = fontmap[font][156];
					break;
				case '\xBD':
					*pText = fontmap[font][157];
					break;
				case '\xBE':
					*pText = fontmap[font][158];
					break;
				case '\xBF':
					*pText = fontmap[font][159];
					break;
				case '\xC0':
					*pText = fontmap[font][160];
					break;
				case '\xC1':
					*pText = fontmap[font][161];
					break;
				case '\xC2':
					*pText = fontmap[font][162];
					break;
				case '\xC3':
					*pText = fontmap[font][163];
					break;
				case '\xC4':
					*pText = fontmap[font][164];
					break;
				case '\xC5':
					*pText = fontmap[font][165];
					break;
				case '\xC6':
					*pText = fontmap[font][166];
					break;
				case '\xC7':
					*pText = fontmap[font][167];
					break;
				case '\xC8':
					*pText = fontmap[font][168];
					break;
				case '\xC9':
					*pText = fontmap[font][169];
					break;
				case '\xCA':
					*pText = fontmap[font][170];
					break;
				case '\xCB':
					*pText = fontmap[font][171];
					break;
				case '\xCC':
					*pText = fontmap[font][172];
					break;
				case '\xCD':
					*pText = fontmap[font][173];
					break;
				case '\xCE':
					*pText = fontmap[font][174];
					break;
				case '\xCF':
					*pText = fontmap[font][175];
					break;
				case '\xD0':
					*pText = fontmap[font][176];
					break;
				case '\xD1':
					*pText = fontmap[font][177];
					break;
				case '\xD2':
					*pText = fontmap[font][178];
					break;
				case '\xD3':
					*pText = fontmap[font][179];
					break;
				case '\xD4':
					*pText = fontmap[font][180];
					break;
				case '\xD5':
					*pText = fontmap[font][181];
					break;
				case '\xD6':
					*pText = fontmap[font][182];
					break;
				case '\xD7':
					*pText = fontmap[font][183];
					break;
				case '\xD8':
					*pText = fontmap[font][184];
					break;
				case '\xD9':
					*pText = fontmap[font][185];
					break;
				case '\xDA':
					*pText = fontmap[font][186];
					break;
				case '\xDB':
					*pText = fontmap[font][187];
					break;
				case '\xDC':
					*pText = fontmap[font][188];
					break;
				case '\xDD':
					*pText = fontmap[font][189];
					break;
				case '\xDE':
					*pText = fontmap[font][190];
					break;
				case '\xDF':
					*pText = fontmap[font][191];
					break;
				case '\xE0':
					*pText = fontmap[font][192];
					break;
				case '\xE1':
					*pText = fontmap[font][193];
					break;
				case '\xE2':
					*pText = fontmap[font][194];
					break;
				case '\xE3':
					*pText = fontmap[font][195];
					break;
				case '\xE4':
					*pText = fontmap[font][196];
					break;
				case '\xE5':
					*pText = fontmap[font][197];
					break;
				case '\xE6':
					*pText = fontmap[font][198];
					break;
				case '\xE7':
					*pText = fontmap[font][199];
					break;
				case '\xE8':
					*pText = fontmap[font][200];
					break;
				case '\xE9':
					*pText = fontmap[font][201];
					break;
				case '\xEA':
					*pText = fontmap[font][202];
					break;
				case '\xEB':
					*pText = fontmap[font][203];
					break;
				case '\xEC':
					*pText = fontmap[font][204];
					break;
				case '\xED':
					*pText = fontmap[font][205];
					break;
				case '\xEE':
					*pText = fontmap[font][206];
					break;
				case '\xEF':
					*pText = fontmap[font][207];
					break;
			}
			pText++;
		}
	}
}
