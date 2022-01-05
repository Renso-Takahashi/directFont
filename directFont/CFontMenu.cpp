/* ###############################################################

Add a menu to configure the mod directly from the game.

Not yet implemented, for now you can only use the cheat
"fontconfig" to reload the configurations and restart the mod...

################################################################*/

#include "CNewFonts.h"
#include <Plugin.h>
#include <CMenuSystem.h>
#include "extensions\ScriptCommands.h"
#include <CCheat.h>
#include <CHud.h>

static const char fontcheat[] = { 'G','I','F','N','O','C','T','N','O','F',
					0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool enabled = false, initialized = false;
ushort counter = 0;
uchar panelID = 0;
CMenuSystem* CFontMenu;
using namespace plugin;

bool CNewFonts::_Running = true;

DWORD WINAPI CNewFonts::FontMenu(void* parameter)
{
	while (_Running) {
		//char *fcheat = _strrev(fontcheat);
		if (FindPlayerPed()) {
			if (!_strnicmp(fontcheat, CCheat::m_CheatString, strlen(fontcheat)))
			{
				if (!enabled) {
					enabled = true;
					CCheat::m_CheatString[0] = '\0';
				}
			}
			if (enabled) {
				Shutdown();
				Sleep(10);
				Initialise();
				Sleep(10);
				MessageBeep(SOUND_SYSTEM_INFORMATION);
				enabled = false;

				//CHud::SetHelpMessage("directFont Config reloaded!", true, false, false);
				/*if (!initialized) {
					FindPlayerPed()->DeactivatePlayerPed(0);
					//CFontMenu->Initialise();

					panelID = CFontMenu->CreateNewMenu(MENU_TYPE_DEFAULT, "DIRFT00", ((screen::GetScreenWidth() / 2.0f) - 200.0f),
						((screen::GetScreenHeight() / 4.0f)), 400.0f, 1, true, true, ALIGN_CENTER);

					CFontMenu->InsertMenuA(panelID, 0, "DIRFT01", "DIRFT05", "DIRFT06", "DIRFT07", "DIRFT08",
						"DIRFT09", "DIRFT10", "DIRFT11", "DIRFT12", "DIRFT13", "DIRFT14", "DIRFT15", "DIRFT16");

					CFontMenu->SetActiveMenuItem(panelID, 0);
					CFontMenu->HighlightOneItem(panelID, 0);

					initialized = true;
				}
				else {
					if (scripting::CallCommandById(Commands::IS_BUTTON_PRESSED, 0, 16))
					{
						switch(CFontMenu->CheckForSelected(panelID))
						{
							case 0:
								CHud::SetHelpMessage("Item 1 selected!", true, false, false);
								break;
							case 1:
								CHud::SetHelpMessage("Item 2 selected!", true, false, false);
								break;
							case 2:
								CHud::SetHelpMessage("Item 3 selected!", true, false, false);
								break;
							case 3:
								CHud::SetHelpMessage("Item 4 selected!", true, false, false);
								break;
							case 4:
								CHud::SetHelpMessage("Item 5 selected!", true, false, false);
								break;
							case 5:
								CHud::SetHelpMessage("Item 6 selected!", true, false, false);
								break;
							case 6:
								CHud::SetHelpMessage("Item 7 selected!", true, false, false);
								break;
							case 7:
								CHud::SetHelpMessage("Item 8 selected!", true, false, false);
								break;
							case 8:
								CHud::SetHelpMessage("Item 9 selected!", true, false, false);
								break;
							case 9:
								CHud::SetHelpMessage("Item 10 selected!", true, false, false);
								break;
							case 10:
								CHud::SetHelpMessage("Item 11 selected!", true, false, false);
								break;
							case 11:
								CHud::SetHelpMessage("Item 12 selected!", true, false, false);
								break;
						}
					}
					if (scripting::CallCommandById(Commands::IS_BUTTON_PRESSED, 0, 15))
					{
						CFontMenu->SwitchOffMenu(panelID);
						panelID = 0;
						initialized = false;
						enabled = false;
						FindPlayerPed()->ReactivatePlayerPed(0);
					}
				}*/
			}
		}
	}

	return 0;
}