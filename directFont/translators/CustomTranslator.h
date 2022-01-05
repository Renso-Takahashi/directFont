#pragma once

#include "BaseTranslation.h"

class CustomTranslator {
public:
    static void TranslateString(char *str, int font);
    static bool Initialize(const char* filename);
protected:
    static bool LoadMap(char* filename, char font);
    //static bool initialized[4];
};