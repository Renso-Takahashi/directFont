// Custom translator by Wyrdgirn
#pragma once

#include "BaseTranslation.h"

class CustomTranslator {
public:
    static void TranslateString(char *str, int font);
    static bool Initialize(const char* filename);
    static bool FileExist(char* filename);
protected:
    static const char FillMap[208];
    static char fontmap[4][208];
    static bool initialized;
};