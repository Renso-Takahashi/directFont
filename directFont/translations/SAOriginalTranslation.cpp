#include "SAOriginalTranslation.h"

#define FONT_00 0
#define FONT_01 1
#define FONT_02 2
#define FONT_03 3

void SAOriginalTranslation::TranslateString(char *str, int Font_Number) {
	char *pText = str;
	while (*pText) {
		switch (*pText)
		{
			/*case '\x20':
				if(Font_Number == FONT_03)
					*pText = '!';
				else
					*pText = ' ';
				break;*/
			case '\x23':
				if(Font_Number == FONT_01)
					*pText = '#';
				else
					*pText = ' ';
				break;
			case '\x26':
				if(Font_Number == FONT_01)
					*pText = '&';
				else
					*pText = ' ';
				break;
			case '\x28':
				*pText = '[';
				break;
			case '\x29':
				*pText = ']';
				break;
			case '\x2A':
				*pText = '&';
				break;
			case '\x3F':
				if(Font_Number == FONT_01)
					*pText = '?';
				else
					*pText = ' ';
				break;
			case '\x40':
				*pText = '�';
				break;
			case '\x5B':
				if(Font_Number == FONT_03)
					*pText = ' ';
				break;
			case '\x5D':
				if(Font_Number == FONT_03)
					*pText = '*';
				break;
			case '\x5E':
				*pText = '�';
				break;
			case '\x60':
				*pText = ' ';
				break;
			case '\x7B':
				*pText = '?';
				break;
			case '\x7C':
				*pText = '�';
				break;
			case '\x7D':
				if(Font_Number == FONT_03)
					*pText = '$';
				else
					*pText = ' ';
				break;
			case '\x7E':
				if(Font_Number == FONT_03)
					*pText = '$';
				else
					*pText = '(';
				break;
			case '\x7F':
				if(Font_Number == FONT_03)
					*pText = ')';
				else
					*pText = ' ';
				break;
			case '\x80':
				*pText = '�';
				break;
			case '\x81':
				*pText = '�';
				break;
			case '\x82':
				*pText = '�';
				break;
			case '\x83':
				*pText = '�';
				break;
			case '\x84':
				*pText = '�';
				break;
			case '\x85':
				*pText = '�';
				break;
			case '\x86':
				*pText = '�';
				break;
			case '\x87':
				*pText = '�';
				break;
			case '\x88':
				*pText = '�';
				break;
			case '\x89':
				*pText = '�';
				break;
			case '\x8A':
				*pText = '�';
				break;
			case '\x8B':
				*pText = '�';
				break;
			case '\x8C':
				*pText = '�';
				break;
			case '\x8D':
				*pText = '�';
				break;
			case '\x8E':
				*pText = '�';
				break;
			case '\x8F':
				*pText = '�';
				break;
			case '\x90':
				*pText = '�';
				break;
			case '\x91':
				*pText = '�';
				break;
			case '\x92':
				*pText = '�';
				break;
			case '\x93':
				*pText = '�';
				break;
			case '\x94':
				*pText = '�';
				break;
			case '\x95':
				*pText = '�';
				break;
			case '\x96':
				*pText = '�';
				break;
			case '\x97':
				*pText = '�';
				break;
			case '\x98':
				*pText = '�';
				break;
			case '\x99':
				*pText = '�';
				break;
			case '\x9A':
				*pText = '�';
				break;
			case '\x9B':
				*pText = '�';
				break;
			case '\x9C':
				*pText = '�';
				break;
			case '\x9D':
				*pText = '�';
				break;
			case '\x9E':
				*pText = '�';
				break;
			case '\x9F':
				*pText = '�';
				break;
			case '\xA0':
				*pText = '�';
				break;
			case '\xA1':
				*pText = '�';
				break;
			case '\xA2':
				*pText = '�';
				break;
			case '\xA3':
				*pText = '�';
				break;
			case '\xA4':
				*pText = '�';
				break;
			case '\xA5':
				*pText = '�';
				break;
			case '\xA6':
				*pText = '�';
				break;
			case '\xA7':
				*pText = '�';
				break;
			case '\xA8':
				*pText = '�';
				break;
			case '\xA9':
				*pText = '�';
				break;
			case '\xAA':
				*pText = '�';
				break;
			case '\xAB':
				*pText = '�';
				break;
			case '\xAC':
				*pText = '�';
				break;
			case '\xAD':
				*pText = '�';
				break;
			case '\xAE':
				*pText = '�';
				break;

			case '\xAF':
				if(Font_Number == FONT_01)
					*pText = '�';
				else
					*pText = ' ';
				break;

			case '\xB0':
				*pText = '0';
				break;
			case '\xB1':
				*pText = '1';
				break;
			case '\xB2':
				*pText = '2';
				break;
			case '\xB3':
				*pText = '3';
				break;
			case '\xB4':
				*pText = '4';
				break;
			case '\xB5':
				*pText = '5';
				break;
			case '\xB6':
				*pText = '6';
				break;
			case '\xB7':
				*pText = '7';
				break;
			case '\xB8':
				*pText = '8';
				break;
			case '\xB9':
				*pText = '9';
				break;

			case '\xBA':
				if(Font_Number == FONT_03)
					*pText = ':';
				else
					*pText = ' ';
				break;

			case '\xBB':
				*pText = 'A';
				break;
			case '\xBC':
				*pText = 'B';
				break;
			case '\xBD':
				*pText = 'C';
				break;
			case '\xBE':
				*pText = 'D';
				break;
			case '\xBF':
				*pText = 'E';
				break;
			case '\xC0':
				*pText = 'F';
				break;
			case '\xC1':
				*pText = 'G';
				break;
			case '\xC2':
				*pText = 'H';
				break;
			case '\xC3':
				*pText = 'I';
				break;
			case '\xC4':
				*pText = 'J';
				break;
			case '\xC5':
				*pText = 'K';
				break;
			case '\xC6':
				*pText = 'L';
				break;
			case '\xC7':
				*pText = 'M';
				break;
			case '\xC8':
				*pText = 'N';
				break;
			case '\xC9':
				*pText = 'O';
				break;
			case '\xCA':
				*pText = 'P';
				break;
			case '\xCB':
				*pText = 'Q';
				break;
			case '\xCC':
				*pText = 'R';
				break;
			case '\xCD':
				*pText = 'S';
				break;
			case '\xCE':
				*pText = 'T';
				break;
			case '\xCF':
				*pText = 'U';
				break;
			case '\xD0':
				*pText = 'V';
				break;
			case '\xD1':
				*pText = 'W';
				break;
			case '\xD2':
				*pText = 'X';
				break;
			case '\xD3':
				*pText = 'Y';
				break;
			case '\xD4':
				*pText = 'Z';
				break;

			case '\xD5':
				*pText = '�';
				break;
			case '\xD6':
				*pText = '�';
				break;
			case '\xD7':
				*pText = '�';
				break;
			case '\xD8':
				*pText = '�';
				break;
			case '\xD9':
				*pText = '�';
				break;
			case '\xDA':
				*pText = '�';
				break;
			case '\xDB':
				*pText = '�';
				break;
			case '\xDC':
				*pText = '�';
				break;
			case '\xDD':
				*pText = '�';
				break;
			case '\xDE':
				*pText = '�';
				break;
			case '\xDF':
				*pText = '�';
				break;
			case '\xE0':
				*pText = '�';
				break;
			case '\xE1':
				*pText = '�';
				break;
			case '\xE2':
				*pText = '�';
				break;
			case '\xE3':
				*pText = '�';
				break;
			case '\xE4':
				*pText = '�';
				break;
			case '\xE5':
				*pText = '�';
				break;
			case '\xE6':
				*pText = '�';
				break;
			case '\xE7':
				*pText = '�';
				break;
			case '\xE8':
				*pText = '�';
				break;
			case '\xE9':
				*pText = '�';
				break;
			case '\xEA':
				*pText = '�';
				break;
			case '\xEB':
				*pText = '�';
				break;
			case '\xEC':
				*pText = '�';
				break;
			case '\xED':
				*pText = '�';
				break;
			case '\xEE':
				if(Font_Number == FONT_03)
					*pText = '\'';
				else
					*pText = ' ';
				break;
			case '\xEF':
				if(Font_Number == FONT_03)
					*pText = '.';
				else
					*pText = ' ';
				break;
		}
		pText++;
	}
}