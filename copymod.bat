@if exist "%GTA_SA_DIR%\scripts\directFont.asi" (
@echo Deleting old directFont.asi file...
@del "C:\Program Files (x86)\Rockstar Games\GTA San Andreas\scripts\directFont.asi"
)
@echo Copying new directFont.asi file...
@copy "%CD%\Rel\directFont.asi" "%GTA_SA_DIR%\scripts\directFont.asi"
@echo Done!