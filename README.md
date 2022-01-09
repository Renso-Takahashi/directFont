# directFont V3 WideFont Edition

 This is a new version of the directFont mod version 2.2 created by DK22Pac and updated by me (Wyrdgirn)


The initial objective was to add support for Latin characters (Spanish, Portuguese...) but now my goal is to give support to more languages which need a set of UNICODE characters which the game does not support natively, for this I use a translator that detects a text and replaces it on the fly with a UNICODE one, thus allowing you to replace any text in the game simply by editing a text file...

For now the WIDE Translator is very limited so it only supports color texts but does not support key insertion using tags...

The WIDE translator is loaded as a separate function allowing the game to still process its original texts, that way the game is able to use both UNICODE characters and non-UNICODE characters...



For now, these would be the changes from DK22Pak v2.2:

- New Latin translator (Internal) (sure but may still contain errors)
- New custom translator: allows you to load a character set from a file. Each file has an individual character set for each font, allowing you to change characters from one font without altering that of the others...
- New WIDE translator: Allows you to replace texts on the fly in addition to supporting UNICODE characters. With it you can bring the game to almost any language (for example Japanese or Chinese) just by editing a simple file
- Fixed some problems with the subtitles which were not kept correctly aligned vertically (still need to correct them a bit...)
- Added the **FONTCONFIG** cheat which allows you to reload the configuration file during the game without having to close it. The Windows notification sound will confirm the changes. It is not recommended to use it frequently in the same game as it can cause crashes!
- Maybe some improvements soon...


*I hope you like the improvements :3*

*Att.: Wyrdgirn*

**My twitter**
https://twitter.com/Wyrdgirn

**You find the latest stable version in**
https://github.com/Renso-Takahashi/directFont/releases

**You can find the mod also in my GTAInside profile**
https://www.gtainside.com/en/sanandreas/mods/167979-directfont-full-latin-support/

**You can find the original source code at**
https://github.com/DK22Pac/directFont
