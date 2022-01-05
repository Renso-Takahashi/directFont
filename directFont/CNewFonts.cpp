/* ###############################################################

 Data conversion is used during calculations because
 there is code where integrals are processed with floats

 I cannot say if it is effective but I suppose it will have
 some impact on the precision with which the texts are
 displayed, positioned and/or scaled...

################################################################*/

#include "CNewFonts.h"
#include "plugin.h"
#include "CSprite2d.h"
#include "CMessages.h"
#include "CHudColours.h"
#include "translators\LatinTranslation.h"
#include "translators\CustomTranslator.h"
#include "translators\SanLtdTranslation.h"
#include "translators\SAOriginalTranslation.h"
#include <stdio.h>

using namespace plugin;

extern LPDIRECT3DDEVICE9 &_RwD3DDevice;
CD3DSprite *CNewFonts::m_pFontSprite;
CNewFont CNewFonts::m_aFonts[4];
eTranslation CNewFonts::m_Translation;
eFontStyle CNewFonts::m_FontId;
CRGBA CNewFonts::gLetterColors[MAX_TEXT_SIZE];
unsigned int CNewFonts::gNumLetters;
bool CNewFonts::gShadow;
static char transln[50];

bool CNewFont::SetupFont(char *fontName, unsigned int width, int height, float scaleX, float scaleY, unsigned int weight, bool italic,
    unsigned int charSet, unsigned int outputPrecision, unsigned int quality, unsigned int pitchAndFamily, bool upperCase,
    bool replaceUS)
{
    HRESULT hr = D3DXCreateFont(CNewFonts::GetCurrentDevice(), width, height, weight, 0, italic, charSet, outputPrecision, quality,
        ((pitchAndFamily == 0) ? pitchAndFamily| FF_DONTCARE : pitchAndFamily), fontName, &m_pD3DXFont);
    if (hr != S_OK) {
        m_pD3DXFont = NULL;
        return Error("CNewFont::SetupFont: Can't load \"%s\" font", fontName);
    }
    m_initialised = true;
    strcpy(m_fontName, fontName);
    m_width = width;
    m_height = height;
    m_scaleX = scaleX;
    m_scaleY = scaleY;
    m_weight = weight;
    m_italic = italic;
    m_charSet = charSet;
    m_outputPrecision = outputPrecision;
    m_quality = quality;
    m_pitchAndFamily = pitchAndFamily;
    m_upperCase = upperCase;
    m_replaceUS = replaceUS;
    return true;
}

void CNewFont::PrintString(char *text, CRect const& rect, float scale_x, float scale_y, CRGBA const& color, DWORD format, CRGBA const* backgroundColor,
    float shadow, float outline, CRGBA const* dropColor)
{
    RECT d3drect; SetRect(&d3drect, (int)rect.left, (int)rect.top, (int)rect.right, (int)rect.bottom);
    if (backgroundColor)
        DrawRect(text, rect, scale_x, scale_y, format, *backgroundColor);
    RECT d3drect2; SetRect(&d3drect2, (int)(d3drect.left / (scale_x / 2)), (int)(d3drect.top / (scale_y / 2)), (int)(d3drect.right / (scale_x / 2)), (int)(d3drect.bottom / (scale_y / 2)));
    D3DXMATRIX S, P;
    D3DXMatrixScaling(&S, scale_x / 2.0f, scale_y / 2.0f, 1.0f);
    CNewFonts::m_pFontSprite->GetTransform(&P);
    CNewFonts::m_pFontSprite->SetTransform(&S);
    CNewFonts::m_pFontSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
    if (shadow > 0.0f) {
        RECT shadowRect(d3drect2);
        shadowRect.left += (long)shadow;
        shadowRect.right += (long)shadow;
        shadowRect.top += (long)shadow;
        shadowRect.bottom += (long)shadow;
        CNewFonts::gShadow = true;
        m_pD3DXFont->DrawText(CNewFonts::m_pFontSprite, text, -1, &shadowRect, format, D3DCOLOR_ARGB(dropColor->a,
            dropColor->r, dropColor->g, dropColor->b));
    }
    else if (outline > 0.0f) {
        RECT outl1(d3drect2);
        outl1.left -= (long)outline;
        outl1.right -= (long)outline;
        CNewFonts::gShadow = true;
        m_pD3DXFont->DrawText(CNewFonts::m_pFontSprite, text, -1, &outl1, format, D3DCOLOR_ARGB(dropColor->a,
            dropColor->r, dropColor->g, dropColor->b));
        RECT outl2(d3drect2);
        outl2.left += (long)outline;
        outl2.right += (long)outline;
        CNewFonts::gShadow = true;
        m_pD3DXFont->DrawText(CNewFonts::m_pFontSprite, text, -1, &outl2, format, D3DCOLOR_ARGB(dropColor->a,
            dropColor->r, dropColor->g, dropColor->b));
        RECT outl3(d3drect2);
        outl3.top -= (long)outline;
        outl3.bottom -= (long)outline;
        CNewFonts::gShadow = true;
        m_pD3DXFont->DrawText(CNewFonts::m_pFontSprite, text, -1, &outl3, format, D3DCOLOR_ARGB(dropColor->a,
            dropColor->r, dropColor->g, dropColor->b));
        RECT outl4(d3drect2);
        outl4.top += (long)outline;
        outl4.bottom += (long)outline;
        CNewFonts::gShadow = true;
        m_pD3DXFont->DrawText(CNewFonts::m_pFontSprite, text, -1, &outl4, format, D3DCOLOR_ARGB(dropColor->a,
            dropColor->r, dropColor->g, dropColor->b));
    }
    CNewFonts::gNumLetters = 0;
    CNewFonts::gShadow = false;
    m_pD3DXFont->DrawText(CNewFonts::m_pFontSprite, text, -1, &d3drect2, format, D3DCOLOR_ARGB(color.a,
        color.r, color.g, color.b));
    CNewFonts::m_pFontSprite->SetTransform(&P);
    CNewFonts::m_pFontSprite->End();
}

void CNewFont::DrawRect(char *text, CRect const& rect, float scale_x, float scale_y, DWORD format, CRGBA const& backgroundColor) {
    float x2 = rect.right;
    RECT d3drect; SetRect(&d3drect, (int)rect.left, (int)rect.top, (int)rect.right, (int)rect.bottom);
    RECT d3drect2; SetRect(&d3drect2, (int)(d3drect.left / (scale_x / 2)), (int)(d3drect.top / (scale_y / 2)), (int)(d3drect.right / (scale_x / 2)), (int)(d3drect.bottom / (scale_y / 2)));
    D3DXMATRIX S, P;
    D3DXMatrixScaling(&S, scale_x / 2.0f, scale_y / 2.0f, 1.0f);
    CNewFonts::m_pFontSprite->GetTransform(&P);
    CNewFonts::m_pFontSprite->SetTransform(&S);
    CNewFonts::m_pFontSprite->Begin(0);
    this->m_pD3DXFont->DrawText(CNewFonts::m_pFontSprite, text, -1, &d3drect2, format | DT_CALCRECT, 0xFFFFFFFF);
    CNewFonts::m_pFontSprite->SetTransform(&P);
    CNewFonts::m_pFontSprite->End();
    CSprite2d::DrawRect(CRect(d3drect2.left*(scale_x / 2.0f) - 8.0f, d3drect2.top*(scale_y / 2.0f) - 8.0f, x2 + 8.0f, (float)d3drect2.bottom*(scale_y / 2.0f) + 8.0f), backgroundColor);
}

void CNewFont::ReleaseFont() {
    if (this->m_pD3DXFont) {
        this->m_pD3DXFont->Release();
        this->m_pD3DXFont = NULL;
    }
}

void CNewFont::OnLost() {
    ReleaseFont();
}

void CNewFont::OnReset() {
    D3DXCreateFont(CNewFonts::GetCurrentDevice(), m_width, m_height, m_weight, 0, m_italic, m_charSet, m_outputPrecision, m_quality,
        m_pitchAndFamily, m_fontName, &this->m_pD3DXFont);
}

float __declspec(naked) _GetWidth() {
    __asm add esp, 0x198
    __asm jmp CNewFonts::GetStringWidth
}

void CNewFonts::Initialise() {
    char app[8], fontName[256], scaleFactorStr[16], translation[16];
    unsigned int fontId, height, weight, charSet, outputPrecision,
        quality, pitchAndFamily;
    int width;
    float scaleX, scaleY;
    bool italic, upperCase,replaceUS;

    for (int i = 0; i < MAX_NUM_FONTS; i++) {
        wsprintf(app, "FONT%d", i + 1);
        GetPrivateProfileString(app, "FontName", "USE_DEFAULT", fontName, 256, PLUGIN_PATH("directFont\\directFont.ini"));
        if (!strcmp(fontName, "USE_DEFAULT")) {
            m_aFonts[i].m_initialised = false;
            continue;
        }
        if (!strncmp(fontName, "USE_FONT", 8)) {
            if (!i) {
                Error("CNewFonts::Initialise\nCan't apply USE_FONT to first font.");
                m_aFonts[i].m_initialised = false;
                continue;
            }
            sscanf(fontName, "USE_FONT%d", &fontId);
            if (fontId > MAX_NUM_FONTS) {
                Error("CNewFonts::Initialise\nUnknown font used with USE_FONT construction.");
                m_aFonts[i].m_initialised = false;
                continue;
            }
            if (fontId == i) {
                Error("CNewFonts::Initialise\nCan't apply USE_FONT to this font.");
                m_aFonts[i].m_initialised = false;
                continue;
            }
            m_aFonts[i].SetupFont(m_aFonts[fontId].m_fontName, m_aFonts[fontId].m_width, m_aFonts[fontId].m_height, m_aFonts[fontId].m_scaleX,
                m_aFonts[fontId].m_scaleY, m_aFonts[fontId].m_weight, m_aFonts[fontId].m_italic, m_aFonts[fontId].m_charSet,
                m_aFonts[fontId].m_outputPrecision, m_aFonts[fontId].m_quality, m_aFonts[fontId].m_pitchAndFamily, m_aFonts[fontId].m_upperCase,
                m_aFonts[fontId].m_replaceUS);
        }
        else {
            height = GetPrivateProfileInt(app, "Height", 64, PLUGIN_PATH("directFont\\directFont.ini"));
            width = GetPrivateProfileInt(app, "Width", 40, PLUGIN_PATH("directFont\\directFont.ini"));
            GetPrivateProfileString(app, "ScaleFactor.x", "0.6", scaleFactorStr, 16, PLUGIN_PATH("directFont\\directFont.ini"));
            sscanf(scaleFactorStr, "%f", &scaleX);
            GetPrivateProfileString(app, "ScaleFactor.y", "0.4", scaleFactorStr, 16, PLUGIN_PATH("directFont\\directFont.ini"));
            sscanf(scaleFactorStr, "%f", &scaleY);
            weight = GetPrivateProfileInt(app, "Weight", 500, PLUGIN_PATH("directFont\\directFont.ini"));
            italic = GetPrivateProfileInt(app, "Italic", 0, PLUGIN_PATH("directFont\\directFont.ini"));
            charSet = GetPrivateProfileInt(app, "CharSet", 1, PLUGIN_PATH("directFont\\directFont.ini"));
            outputPrecision = GetPrivateProfileInt(app, "OutputPrecision", 0, PLUGIN_PATH("directFont\\directFont.ini"));
            quality = GetPrivateProfileInt(app, "Quality", 0, PLUGIN_PATH("directFont\\directFont.ini"));
            pitchAndFamily = GetPrivateProfileInt(app, "PitchAndFamily", 0, PLUGIN_PATH("directFont\\directFont.ini"));
            upperCase = GetPrivateProfileInt(app, "UpcaseAlways", 0, PLUGIN_PATH("directFont\\directFont.ini"));
            replaceUS = GetPrivateProfileInt(app, "ReplaceUnderscoreWithSpace", 0, PLUGIN_PATH("directFont\\directFont.ini"));
            m_aFonts[i].SetupFont(fontName, width, height, scaleX, scaleY, weight, italic, charSet, outputPrecision, quality, pitchAndFamily,
                upperCase, replaceUS);
        }
    }

    // Added the Custom Translator
    GetPrivateProfileString("GENERAL", "UseTranslator", "NONE", translation, 16, PLUGIN_PATH("directFont\\directFont.ini"));
    if (!strncmp(translation, "NONE", 4))
        m_Translation = eTranslation::TRANSLATION_NONE;
    else if (!strncmp(translation, "SANLTD", 6))
        m_Translation = eTranslation::TRANSLATION_SANLTD;
	else if (!strncmp(translation, "LATIN", 5))
		m_Translation = eTranslation::TRANSLATION_LATIN;
	/*else if (!strncmp(translation, "CUSTOM", 6))
		m_Translation = eTranslation::TRANSLATION_CUSTOM;
	else if (!strncmp(translation, "WIDE", 6))
		m_Translation = eTranslation::TRANSLATION_WIDE;*/
    else {
        Error("CNewFonts::Initialise\nUnknown translation name.");
        m_Translation = eTranslation::TRANSLATION_NONE;
    }

    // Load the custom translator
    if (m_Translation == eTranslation::TRANSLATION_CUSTOM)
    {
        GetPrivateProfileString("GENERAL", "CustomTranslator", "NONE", transln, 50, PLUGIN_PATH("directFont\\directFont.ini"));
        transln[strlen(transln)] = '\0';
        CustomTranslator tr;
        if (!tr.Initialize(transln)) {
            Error("CNewFonts::Initialise\nCan't load the Custom Translator.");
            m_Translation = eTranslation::TRANSLATION_NONE;
        }
    }

    patch::RedirectJump(0x71A700, PrintString);
    patch::RedirectJump(0x71A0E6, _GetWidth);
    patch::SetChar(0x58DCEF, '*');
    patch::RedirectJump(0x719490, SetFontStyle);
    m_pFontSprite = new CD3DSprite;

    _Running = true;
    CreateThread(NULL,NULL,CNewFonts::FontMenu,NULL,NULL,NULL);
}

void CNewFonts::Reset() {
    for (int i = 0; i < MAX_NUM_FONTS; i++) {
        if (m_aFonts[i].m_initialised)
            m_aFonts[i].OnReset();
    }
    if (m_pFontSprite)
        m_pFontSprite->OnResetDevice();
}

void CNewFonts::Lost() {
    for (int i = 0; i < MAX_NUM_FONTS; i++) {
        if (m_aFonts[i].m_initialised)
            m_aFonts[i].OnLost();
    }
    if (m_pFontSprite)
        m_pFontSprite->OnLostDevice();
}

void CNewFonts::Shutdown() {
    _Running = false;
    for (int i = 0; i < MAX_NUM_FONTS; i++) {
        if (m_aFonts[i].m_initialised)
            m_aFonts[i].ReleaseFont();
    }
    delete m_pFontSprite;
}

IDirect3DDevice9 *CNewFonts::GetCurrentDevice() {
    return _RwD3DDevice;
}

void _UpCase(char *str) {
    char *pStr = str;
    while (*pStr) {
        if ((*pStr >= 'a' && *pStr <= 'z') || (*pStr >= 'à' && *pStr <= 'ÿ'))
            *pStr -= 0x20;
        else if (*pStr == '·')
            *pStr = '§';
        pStr++;
    }
}

void ReplaceUsWithSpace(unsigned char *str) {
    unsigned char *pStr = str;
    while (*pStr) {
        if (*pStr == '\x5F')
            *pStr = ' ';
        pStr++;
    }
}

void CNewFonts::PrintString(float x, float y, char *text) {
    if (m_aFonts[m_FontId].m_initialised) {
        static char taggedText[MAX_TEXT_SIZE];

        // FillMemory fills the variable with zeros, preventing GetStringWidth()
        // from detecting old text fragments and causing text alignment problems
        // when returning a larger value
        // (Visible in the subtitles where there are texts that appear higher even
        // having only one line ...) 

        FillMemory(taggedText, MAX_TEXT_SIZE, 0);

        CRect *rect;
        unsigned int flag;
        if (CFont::m_bFontCentreAlign) {
            rect = &CRect(x - CFont::m_fFontCentreSize / 2.0f, y, x + CFont::m_fFontCentreSize / 2.0f, SCREEN_HEIGHT);
            flag = DT_CENTER;
        }
        else if (CFont::m_bFontRightAlign) {
            rect = &CRect(CFont::m_fRightJustifyWrap, y, x, SCREEN_HEIGHT);
            flag = DT_RIGHT;
        }
        else {
            rect = &CRect(x, y, CFont::m_fWrapx, SCREEN_HEIGHT);
            flag = DT_LEFT;
        }
        ProcessTags(taggedText, text);
        if (m_Translation == eTranslation::TRANSLATION_SANLTD) {
            SanLtdTranslation tr;
            tr.TranslateString(taggedText);
        } else if (m_Translation == eTranslation::TRANSLATION_LATIN) {
			LatinTranslation tr;
			tr.TranslateString(taggedText);
		} else if (m_Translation == eTranslation::TRANSLATION_CUSTOM) {
            // Load a different character map per font
            CustomTranslator tr;
			tr.TranslateString(taggedText, m_FontId);
		}
        if (m_aFonts[m_FontId].m_upperCase)
            _UpCase((char *)taggedText);
        if (m_aFonts[m_FontId].m_replaceUS)
            ReplaceUsWithSpace((unsigned char *)taggedText);
        m_aFonts[m_FontId].PrintString(taggedText, *rect, CFont::m_Scale->x * m_aFonts[m_FontId].m_scaleX,
            CFont::m_Scale->y * m_aFonts[m_FontId].m_scaleY, *CFont::m_Color,
            DT_TOP | DT_NOCLIP | DT_WORDBREAK | flag, CFont::m_bFontBackground ? CFont::m_FontBackgroundColor : NULL,
            (float)(CFont::m_nFontShadow * 2), (float)(CFont::m_nFontOutlineSize * 2), CFont::m_FontDropColor);
    }
    else
        CFont::PrintString(x, y, text);
}

HRESULT CD3DSprite::Draw(LPDIRECT3DTEXTURE9 pTexture, CONST RECT * pSrcRect, CONST D3DXVECTOR3 * pCenter,
    CONST D3DXVECTOR3 * pPosition, D3DCOLOR Color)
{
    HRESULT result;
    if (CNewFonts::gShadow)
        result = m_pSprite->Draw(pTexture, pSrcRect, pCenter, pPosition, Color);
    else {
        result = m_pSprite->Draw(pTexture, pSrcRect, pCenter, pPosition, D3DCOLOR_RGBA(CNewFonts::gLetterColors[CNewFonts::gNumLetters].r,
            CNewFonts::gLetterColors[CNewFonts::gNumLetters].g, CNewFonts::gLetterColors[CNewFonts::gNumLetters].b, 
            CNewFonts::gLetterColors[CNewFonts::gNumLetters].a));
        CNewFonts::gNumLetters++;
    }
    return result;
}

void CNewFonts::ProcessTags(char *dest, char *src) {
    static char text[MAX_TEXT_SIZE];

    // You will already know the reason for the FillMemory
    // if you saw my other comment :P
    FillMemory(text, MAX_TEXT_SIZE, 0);

    //char *pDest = dest, *pText = text;
    strncpy_s(text, src, strlen(src));
    CMessages::InsertPlayerControlKeysInString(text);
    char *outText = dest;
    CRGBA currColor(*CFont::m_Color);
    unsigned int numLetters = 0, txtidx = 0;
    for (size_t i = 0; i <= strlen(text); i++)
    {
        if (i == strlen(text))
        {
            *outText = '\0';
            break;
        } else if (text[i] == '~' && text[i + 2] == '~')
        {
            i++;
            switch (text[i])
            {
                case 'N':
                case 'n':
                    *outText = '\x0A';
                    outText++;
                    i++;
                    break;
                case 'R':
                case 'r':
                    currColor = CRGBA(HudColour.GetRGB(0, CFont::m_Color->a));
                    i++;
                    break;
                case 'G':
                case 'g':
                    currColor = CRGBA(HudColour.GetRGB(1, CFont::m_Color->a));
                    i++;
                    break;
                case 'B':
                case 'b':
                    currColor = CRGBA(HudColour.GetRGB(2, CFont::m_Color->a));
                    i++;
                    break;
                case 'W':
                case 'w':
                    currColor = CRGBA(HudColour.GetRGB(4, CFont::m_Color->a));
                    i++;
                    break;
                case 'H':
                case 'h':
                    currColor = CRGBA((unsigned char)(min((float)CFont::m_Color->r * 1.5f, 255.0f)),
                        (unsigned char)(min((float)CFont::m_Color->g * 1.5f, 255.0f)),
                        (unsigned char)(min((float)CFont::m_Color->b * 1.5f, 255.0f)),
                        CFont::m_Color->a);
                    i++;
                    break;
                case 'Y':
                case 'y':
                    currColor = CRGBA(HudColour.GetRGB(11, CFont::m_Color->a));
                    i++;
                    break;
                case 'P':
                case 'p':
                    currColor = CRGBA(HudColour.GetRGB(7, CFont::m_Color->a));
                    i++;
                    break;
                case 'L':
                case 'l':
                    currColor = CRGBA(HudColour.GetRGB(5, CFont::m_Color->a));
                    i++;
                    break;
                case 'S':
                case 's':
                    currColor = CRGBA(HudColour.GetRGB(4, CFont::m_Color->a));
                    i++;
                    break;
                default:
                    i++;
                    break;
            }
        } else {
            *outText = text[i];
            if (text[i] != ' ') {
                gLetterColors[numLetters] = currColor;
                numLetters++;
            }
            outText++;
        }
    }
}

float CNewFonts::GetStringWidth(char *str, char bFull, char bScriptText) {
    if (m_aFonts[m_FontId].m_initialised) {
        static char text[MAX_TEXT_SIZE];
        static char taggedText[MAX_TEXT_SIZE];

        // Well history repeats itself XD
        // You already know what the FillMemory is for :P
        FillMemory(text, MAX_TEXT_SIZE, 0);
        FillMemory(taggedText, MAX_TEXT_SIZE, 0);

        char *pText = taggedText;
        strncpy(text, str, strlen(str));
        CNewFonts::ProcessTags(taggedText, text);
        if (!bFull)
        {
            while (*pText && *pText != ' ')
                pText++;
            *pText = '\0';
        }
        return CNewFonts::m_aFonts[m_FontId].GetStringWidth(taggedText);
    }
    else
        return CFont::GetStringWidth(str, bFull, bScriptText);
}

float CNewFont::GetStringWidth(char *str) {
    float scale_x = CFont::m_Scale->x * m_scaleX;
    float scale_y = CFont::m_Scale->y * m_scaleY;
    RECT d3drect; SetRect(&d3drect, 0, 0, 0, 0);
    D3DXMATRIX S, P;
    D3DXMatrixScaling(&S, scale_x / 2.0f, scale_y / 2.0f, 1.0f);
    CNewFonts::m_pFontSprite->GetTransform(&P);
    CNewFonts::m_pFontSprite->SetTransform(&S);
    CNewFonts::m_pFontSprite->Begin(0);
    this->m_pD3DXFont->DrawText(CNewFonts::m_pFontSprite, str, -1, &d3drect, DT_TOP | DT_NOCLIP | DT_SINGLELINE | DT_CALCRECT, 0xFFFFFFFF);
    CNewFonts::m_pFontSprite->SetTransform(&P);
    CNewFonts::m_pFontSprite->End();

    // Values are enclosed between "(" and ")" to prevent the function from
    // returning the wrong value...
    return (((float)d3drect.right - (float)d3drect.left) * scale_x) / 2.0f;
}

void CNewFonts::SetFontStyle(eFontStyle style) {
    m_FontId = style;
    if (style == 2) {
        CFont::m_FontTextureId = 0;
        CFont::m_FontStyle = 2;
    }
    else if (style == 3) {
        CFont::m_FontTextureId = 1;
        CFont::m_FontStyle = 1;
    }
    else {
        CFont::m_FontTextureId = style;
        CFont::m_FontStyle = 0;
        CFont::m_FontStyle = 0;
    }
}
