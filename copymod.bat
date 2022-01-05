@if exist "C:\Program Files (x86)\Rockstar Games\GTA San Andreas\scripts\directFont.asi" (
@echo Deleting old directFont.asi file...
@del "C:\Program Files (x86)\Rockstar Games\GTA San Andreas\scripts\directFont.asi"
)
@echo Copying new directFont.asi file...
@copy "C:\Users\Miku Koemi\Source\Repos\Renso-Takahashi\directFont\Rel\directFont.asi" "C:\Program Files (x86)\Rockstar Games\GTA San Andreas\scripts\directFont.asi"
@echo Done!