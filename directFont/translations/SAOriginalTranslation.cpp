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
				*pText = '¡';
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
				*pText = '¡';
				break;
			case '\x60':
				*pText = ' ';
				break;
			case '\x7B':
				*pText = '?';
				break;
			case '\x7C':
				*pText = '°';
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
				*pText = 'À';
				break;
			case '\x81':
				*pText = 'Á';
				break;
			case '\x82':
				*pText = 'Â';
				break;
			case '\x83':
				*pText = 'Ä';
				break;
			case '\x84':
				*pText = 'Æ';
				break;
			case '\x85':
				*pText = 'Ç';
				break;
			case '\x86':
				*pText = 'È';
				break;
			case '\x87':
				*pText = 'É';
				break;
			case '\x88':
				*pText = 'Ê';
				break;
			case '\x89':
				*pText = 'Ë';
				break;
			case '\x8A':
				*pText = 'Ì';
				break;
			case '\x8B':
				*pText = 'Í';
				break;
			case '\x8C':
				*pText = 'Î';
				break;
			case '\x8D':
				*pText = 'Ï';
				break;
			case '\x8E':
				*pText = 'Ò';
				break;
			case '\x8F':
				*pText = 'Ó';
				break;
			case '\x90':
				*pText = 'Ô';
				break;
			case '\x91':
				*pText = 'Ö';
				break;
			case '\x92':
				*pText = 'Ù';
				break;
			case '\x93':
				*pText = 'Ú';
				break;
			case '\x94':
				*pText = 'Û';
				break;
			case '\x95':
				*pText = 'Ü';
				break;
			case '\x96':
				*pText = 'ß';
				break;
			case '\x97':
				*pText = 'à';
				break;
			case '\x98':
				*pText = 'á';
				break;
			case '\x99':
				*pText = 'â';
				break;
			case '\x9A':
				*pText = 'ä';
				break;
			case '\x9B':
				*pText = 'æ';
				break;
			case '\x9C':
				*pText = 'ç';
				break;
			case '\x9D':
				*pText = 'è';
				break;
			case '\x9E':
				*pText = 'é';
				break;
			case '\x9F':
				*pText = 'ê';
				break;
			case '\xA0':
				*pText = 'ë';
				break;
			case '\xA1':
				*pText = 'ì';
				break;
			case '\xA2':
				*pText = 'í';
				break;
			case '\xA3':
				*pText = 'î';
				break;
			case '\xA4':
				*pText = 'ï';
				break;
			case '\xA5':
				*pText = 'ò';
				break;
			case '\xA6':
				*pText = 'ó';
				break;
			case '\xA7':
				*pText = 'ô';
				break;
			case '\xA8':
				*pText = 'ö';
				break;
			case '\xA9':
				*pText = 'ù';
				break;
			case '\xAA':
				*pText = 'ú';
				break;
			case '\xAB':
				*pText = 'û';
				break;
			case '\xAC':
				*pText = 'ü';
				break;
			case '\xAD':
				*pText = 'Ñ';
				break;
			case '\xAE':
				*pText = 'ñ';
				break;

			case '\xAF':
				if(Font_Number == FONT_01)
					*pText = '¿';
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
				*pText = 'À';
				break;
			case '\xD6':
				*pText = 'Á';
				break;
			case '\xD7':
				*pText = 'Â';
				break;
			case '\xD8':
				*pText = 'Ä';
				break;
			case '\xD9':
				*pText = 'Æ';
				break;
			case '\xDA':
				*pText = 'Ç';
				break;
			case '\xDB':
				*pText = 'È';
				break;
			case '\xDC':
				*pText = 'É';
				break;
			case '\xDD':
				*pText = 'Ê';
				break;
			case '\xDE':
				*pText = 'Ë';
				break;
			case '\xDF':
				*pText = 'Ì';
				break;
			case '\xE0':
				*pText = 'Í';
				break;
			case '\xE1':
				*pText = 'Î';
				break;
			case '\xE2':
				*pText = 'Ï';
				break;
			case '\xE3':
				*pText = 'Ò';
				break;
			case '\xE4':
				*pText = 'Ó';
				break;
			case '\xE5':
				*pText = 'Ô';
				break;
			case '\xE6':
				*pText = 'Ö';
				break;
			case '\xE7':
				*pText = 'Ù';
				break;
			case '\xE8':
				*pText = 'Ú';
				break;
			case '\xE9':
				*pText = 'Û';
				break;
			case '\xEA':
				*pText = 'Ü';
				break;
			case '\xEB':
				*pText = 'ß';
				break;
			case '\xEC':
				*pText = 'Ñ';
				break;
			case '\xED':
				*pText = '¿';
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