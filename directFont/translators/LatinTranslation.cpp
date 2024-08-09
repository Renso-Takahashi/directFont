// Wyrdgirn: I don't remember if I edit this file...
#include "LatinTranslation.h"

void LatinTranslation::TranslateString(char *str) {
    char *pText = str;
    while (*pText) {
		switch (*pText)
		{
			case '\x5E':
				*pText = '¡';
				break;
			case '\x7B':
				*pText = '?';
				break;
			case '\x7C':
				*pText = '°';
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
				*pText = '¿';
				break;
			case '\xBA':
				*pText = ':';
				break;
		}
        pText++;
    }
}
