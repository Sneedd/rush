


Rush Utility Library
===============================================================================
Die Rush Utility Library ist eine einfach zu Bediende Klassenbibliotek, ohne
kompizierte Programmierkonstrukte, wie sie in der std vorkommen.

Der Name "Rush" kommt von dem Hund von MegaMan, der ihn bei seinen Abenteuern
unterst�tzt hat.




Konfiguration
===============================================================================
Die Defines k�nnen in der Datei "config.h" eingetragen werden oder aber
�ber den Compiler. Beispiel MinGW: -D_RUSH_WINDOWS_

#define _RUSH_LINUX_                Linux Unterst�tzung
#define _RUSH_WINDOWS_              Windows Unterst�tzung

#define _RUSH_SUPPORTS_STD_         std Klassenbiliothek Unterst�tzung
#define _RUSH_SUPPORTS_WXWIDGETS_   wxWidgets Klassenbiliothek Unterst�tzung

#define _RUSH_UNICODE_              Unicode Unterst�tzung



